#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include"mympi.h"
#include<time.h>
#define DIMS 2000
#define BLOCK_SIZE 32
//设置DCU的个数
#define DCU_NUM 1
//假定每块DCU的处理速度是CPU的SPEED_UP倍
#define SPEED_UP 100
__global__ void MatMulKernel(float *A, float *B, float *C, int m1, int n1, int n2)
{
    int y = hipBlockIdx_y * hipBlockDim_y + hipThreadIdx_y;
    int x = hipBlockIdx_x * hipBlockDim_x + hipThreadIdx_x;
    if(x < n2 && y < m1){
        int tmp = 0;
        for(int n = 0; n < n1; n++){
            tmp += A[y * n1 + n] * B[n * n2 + x];
        }
        C[y * n2 + x] += tmp;
    }
}
void  Mul_Matrixdcu(float *A, float *B, float *C, int m1, int n1, int n2)
{
    float *d_A, *d_B, *d_C;
    size_t sizeA = n1 * m1 * sizeof(float);
    size_t sizeB = n2 * m1 * sizeof(float);
    size_t sizeC = n1 * n2 * sizeof(float);
    //在设备端（dcu）申请地址空间，以存储数据
    hipMalloc(&d_A, sizeA);
    hipMalloc(&d_B, sizeB);
    hipMalloc(&d_C, sizeC);
    //将主机端数据传输到dcu以做计算
    hipMemcpy(d_A, A, sizeA, hipMemcpyHostToDevice);
    hipMemcpy(d_B, B, sizeB, hipMemcpyHostToDevice);
    //这里将C也传进去，因为可能有一部分计算值已经在C中了
    hipMemcpy(d_C, C, sizeC, hipMemcpyHostToDevice);
    dim3 dimBlock(BLOCK_SIZE,BLOCK_SIZE);
    dim3 dimGrid((n2-1)/BLOCK_SIZE + 1, (m1-1)/BLOCK_SIZE + 1);
    //调用核函数
    hipLaunchKernelGGL(MatMulKernel,dimGrid,dimBlock,0,0,d_A,d_B,d_C, m1, n1, n2);
    //将dcu计算的数据传回主机端
    hipMemcpy(C, d_C, sizeC, hipMemcpyDeviceToHost);
    hipFree(d_A);
    hipFree(d_B);
    hipFree(d_C);
}
int main(int argc, char *argv[]){
    float *A,*B,*C,*tempA,*tempC;
    int world_rank, world_size,*lens,*displs,temp,i;
    double start_time, end_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    //总进程数需要大于等于DCU_NUM
    if(world_size<DCU_NUM){
        printf("总进程数world_size应大于等于DCU_NUM(%d)!!!\n",DCU_NUM);
        MPI_Finalize();
        return 0;
    }
    //为所有进程创建B的空间并在0进程进行初始化
    B=(float *)malloc(sizeof(float)*DIMS*DIMS);
    //lens存储每个进程处理的矩阵行数
    lens=(int *)malloc(sizeof(int)*world_size);
    displs=(int *)malloc(sizeof(int)*world_size);

    if(world_rank==0){
        A=(float *)malloc(sizeof(float)*DIMS*DIMS);
        C=(float *)malloc(sizeof(float)*DIMS*DIMS);
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
        Init_Matrix(C,DIMS*DIMS,1);
        //进程0~DCU_NUM-1
        temp=SPEED_UP*DIMS/(DCU_NUM*SPEED_UP+world_size-DCU_NUM);
        for (i = 0;i < DCU_NUM; i++){
            //lens[i]为DIMS的整数倍
            lens[i]=temp*DIMS;
        }
        temp=DIMS-temp*DCU_NUM;
        if(world_size>DCU_NUM){
            //进程DCU_NUM~world_size-1
            if(temp%(world_size-DCU_NUM)==0){
                temp/=(world_size-DCU_NUM);
                for(i=DCU_NUM;i<world_size;i++){
                    lens[i]=temp*DIMS;
                }
            }else{
                for(i=DCU_NUM;i<world_size-1;i++){
                    lens[i]=(temp/(world_size-DCU_NUM))*DIMS;
                }
                lens[world_size-1]=(temp-(temp/(world_size-DCU_NUM))*(world_size-DCU_NUM-1))*DIMS;
                }
        }
        //计算偏移量
        displs[0]=0;
        for(i=1;i<world_size;i++){
            displs[i]=lens[i-1]+displs[i-1];
        }
    }
    start_time=MPI_Wtime();
    //广播矩阵B以及lens到其他所有进程
    MPI_Bcast(B,DIMS*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    MPI_Bcast(lens,world_size,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(displs,world_size,MPI_INT,0,MPI_COMM_WORLD);
    //根据所写核函数，需分配DIMS维方阵的空间，多余部分空间补0
    tempA=(float *)malloc(sizeof(float)*DIMS*DIMS);
    tempC=(float *)malloc(sizeof(float)*DIMS*DIMS);

    //0进程分发A的不同行到其他所有进程
    MPI_Scatterv(A,lens,displs,MPI_FLOAT,tempA,lens[world_rank],MPI_FLOAT,0,MPI_COMM_WORLD);
    if(world_rank<DCU_NUM){
        //设置DCU编号
        hipSetDevice(world_rank);
        Mul_Matrixdcu(tempA,B,tempC,DIMS,DIMS,DIMS);
    }else{
        Mul_Matrix(tempA,B,tempC,lens[world_rank]/DIMS,DIMS,DIMS);
    }
    MPI_Gatherv(tempC,lens[world_rank],MPI_FLOAT,C,lens,displs,MPI_FLOAT,0,MPI_COMM_WORLD);
    end_time=MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",world_rank,(end_time-start_time));
    if(world_rank==0){
        // Verify_matrix_c(A,B,C,DIMS,DIMS,DIMS);
        free(A);
        free(C);
    }
    free(B);
    free(tempA);
    free(tempC);
    free(lens);
    free(displs);
    MPI_Finalize();
    return 0;
}