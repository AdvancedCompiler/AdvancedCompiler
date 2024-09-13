#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include"mympi.h"
#define DIMS 1000
int main(int argc,char *argv[]){
    data_t *A,*B,*C,i;
    double start_time,end_time;

    A=(data_t*)malloc(sizeof(data_t)*DIMS*DIMS);
    B=(data_t*)malloc(sizeof(data_t)*DIMS*DIMS);
    C=(data_t*)malloc(sizeof(data_t)*DIMS*DIMS);
    //初始化A和B矩阵
    //初始化函数传参2意味随机生成0/1矩阵，传入1代表生成0矩阵
    Init_Matrix(A,DIMS*DIMS,2);
    Init_Matrix(B,DIMS*DIMS,2);
    Init_Matrix(C,DIMS*DIMS,1);
    start_time=(double)clock();
    //矩阵A与B相乘，结果存于矩阵C
    Mul_Matrix(A,B,C,DIMS,DIMS,DIMS);
    end_time=(double)clock();
    printf("进程的执行时间为:%.2lf\n",(end_time-start_time)/1e3);
    free(A);
    free(B);
    free(C);
    return 0;
}
