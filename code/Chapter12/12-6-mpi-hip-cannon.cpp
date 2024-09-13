#include "hip/hip_runtime.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"mympi.h"
#include<time.h>
#define DIMS 2000
#define BLOCK_SIZE 32
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
    int id,p,part,num,i,
    upRank,downRank,leftRank,rightRank;
    float *a, *b, *c;
    float *A,*B,*C;
    int coord[2],x,y;//本进程坐标
    int position[2] = {0, 0};//确定（0，0）位置上的进程id
    double start_time, end_time;
    MPI_Comm MPI_COMM_CART;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    int periodic[2];
    int size[2];
    part = sqrt(p);
    //如果进程数不是平方数，则终止进程
    if(part*part!=p){
        printf("总进程数必须是一个平方数!\n");
        MPI_Finalize();
        return 0;
    }
    //如果行数不是进程数的整数倍
    if(DIMS%p!=0){
        printf("总进程数开方之后必须能整除矩阵总行数!\n");
        MPI_Finalize();
        return 0;
    }
    num = DIMS/part;
    //建立笛卡尔通信域
    size[0] = size[1] = part;//虚拟拓扑维数
    periodic[0] = periodic[1] = 1;//虚拟拓扑中进程下标是否循环
    MPI_Cart_create(MPI_COMM_WORLD, 2, size, periodic, 1, &MPI_COMM_CART);
    MPI_Comm_rank(MPI_COMM_CART,&id);
    MPI_Cart_coords(MPI_COMM_CART,id,2,coord);
    x = coord[0];
    y = coord[1];
    //为各个进程分配对应部分块矩阵的空间
    a = (float *)malloc(sizeof(float)*num*num);
    b = (float *)malloc(sizeof(float)*num*num);
    c = (float *)malloc(sizeof(float)*num*num);
    if (id==0){
        A = (float *)malloc(sizeof(float)*DIMS*DIMS);
        B = (float *)malloc(sizeof(float)*DIMS*DIMS);
        C = (float *)malloc(sizeof(float)*DIMS*DIMS);
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
    }
    start_time = MPI_Wtime();
    //分发矩阵
    Matrix_cannon_scatter(DIMS,id,num,part,A,a,MPI_COMM_CART);
    Matrix_cannon_scatter(DIMS,id,num,part,B,b,MPI_COMM_CART);
    Init_Matrix(c,num*num,1);
    //获得当前矩阵块横坐标方向相聚x的左右方向的邻居进程号
    //分块a循环左移x位
    MPI_Cart_shift(MPI_COMM_CART, 1, x, &leftRank, &rightRank);
    MPI_Sendrecv_replace(a, num*num, MPI_FLOAT, leftRank, 0, rightRank, 0, MPI_COMM_CART, &status);
    //获得当前矩阵块纵坐标方向相聚y的上下邻居进程号
    //分块b循环上移y位
    MPI_Cart_shift(MPI_COMM_CART, 0, y, &upRank, &downRank);
    MPI_Sendrecv_replace(b, num*num, MPI_FLOAT, upRank, 0, downRank, 0, MPI_COMM_CART, &status);
    //获取上下左右相邻进程的进程号
    MPI_Cart_shift(MPI_COMM_CART, 0, 1, &upRank, &downRank);
    MPI_Cart_shift(MPI_COMM_CART, 1, 1, &leftRank, &rightRank);
    //进行余下part次循环位移，并计算分块c
    //设置DCU编号
    if(id<4){
        hipSetDevice(id);
    }
    for (i = 0; i < part; ++i){
        //每次计算得到的c都会和原有的c对应相加
        Mul_Matrixdcu(a,b,c,num,num,num);
        MPI_Sendrecv_replace(a, num*num, MPI_FLOAT, leftRank, 0, rightRank, 0, MPI_COMM_CART, &status);
        MPI_Sendrecv_replace(b, num*num, MPI_FLOAT, upRank, 0, downRank, 0, MPI_COMM_CART, &status);
    }
    //收集矩阵C
    Matrix_cannon_gather(DIMS,id,num,part,c,C,MPI_COMM_CART);
    end_time = MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",id,(end_time-start_time));
    MPI_Comm_free(&MPI_COMM_CART);
	if (id==0){
        free(A);
        free(B);
        free(C);
    }
    free(a);
    free(b);
    free(c);
    MPI_Finalize();
    return 0;
}