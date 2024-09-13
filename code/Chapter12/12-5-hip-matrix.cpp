#include <stdio.h>
#include <stdlib.h>
#include "mympi.h"
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

#define DIMS 1000
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
int main(int argc,char **argv){
    float *A,*B,*C;
    double start_time,end_time;
    A=(float*)malloc(sizeof(float)*DIMS*DIMS);
    B=(float*)malloc(sizeof(float)*DIMS*DIMS);
    C=(float*)malloc(sizeof(float)*DIMS*DIMS);
    Init_Matrix(A,DIMS*DIMS,2);
    Init_Matrix(B,DIMS*DIMS,2);
    Init_Matrix(C,DIMS*DIMS,1);
    //start
    start_time=(double)clock();
    Mul_Matrixdcu(A,B,C,DIMS,DIMS,DIMS);
    //end
    end_time=(double)clock();
    printf("进程的执行时间为:%.2lf\n",(end_time-start_time)/1e6); 
    // Verify_matrix_c(A,B,C,DIMS,DIMS,DIMS);
    free(A);
    free(B);
    free(C);
    return 0;
}
