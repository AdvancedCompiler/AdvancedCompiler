//mympi.h
#ifndef MYMPI_H_INCLUDE
#define MYMPI_H_INCLUDE
#include<stdlib.h>
#include<time.h>
#include"mpi.h"
//将一个matrix指向的length长度的一维空间初始化
//初始化的数据由随机数模mod后产生的
void Init_Matrix(float *matrix,int length,int mod);
//m1*n1维的A和n1*n2维的B相乘，存于m1*n2维的C中
void Mul_Matrix(float *A,float *B,float *C,int m1,int n1,int n2);
//Cannon算法中分配子矩阵给各进程。
void Matrix_cannon_scatter(int N,int id,int num,int part,float *source_matrix,float *target_matrix,MPI_Comm MPI_COMM_CART);
//按列分解的矩阵算法分发矩阵A
void Matrix_col_scatter(int my_id,float *source_matrix,float *target_matrix,int dims,int col,int count_p,MPI_Comm comm);
//Cannon算法最后聚合C矩阵
void Matrix_cannon_gather(int N,int id,int num,int part,float *source_c,float *target_c,MPI_Comm MPI_COMM_CART);
//打印矩阵，用于测试
void Print_matrix(float *matrix,int m,int n);
//验证结果正确性，用于测试
void Verify_matrix_c(float *A,float * B,float *C,int m1,int n1,int n2);

void Init_Matrix(float *matrix,int length,int mod){
    srand((int)time(0));//设置随机种子
    int i,j;
    for(i=0;i<length;i++){
        matrix[i]=rand()%mod;
    }
}
void Mul_Matrix(float *A,float *B,float *C,int m1,int n1,int n2){
    int i,j,k,temp;
    for (i = 0; i < m1; i++){
        for (j = 0; j < n2; j++){
            temp =0;
            for (k = 0; k < n1; k++){
                temp += A[i * n1 + k] * B[k * n2 + j];
            }
            C[i * n2 + j]+= temp;
        }
    }
}

void Matrix_cannon_scatter(int N,int id,int num,int part,float *source_matrix,float *target_matrix,MPI_Comm MPI_COMM_CART){
    float *matrixpool;//用于分发矩阵的一维向量
    int i,j,w,h,count=0;
    if(id==0){//(0,0)进程
		matrixpool=(float *)malloc(sizeof(float)*N*N);
        //将矩阵source_matrix重新排序放入matrixpool
        for(w=0;w<part;w++)
            for(h=0;h<part;h++)
                for(i=w*num;i<(w+1)*num;i++)
                    for(j=h*num;j<(h+1)*num;j++)
                        matrixpool[count++] = source_matrix[i*N+j]; 
    }
    MPI_Scatter(matrixpool,num*num,MPI_FLOAT,target_matrix,num*num,MPI_FLOAT,0,MPI_COMM_CART);
    if(id==0){
        free(matrixpool);
	}
}
void Matrix_cannon_gather(int N,int id,int num,int part,float *source_c,float *target_c,MPI_Comm MPI_COMM_CART){
    float *matrixpool;//用于收集C矩阵的一维向量
    int i,j,w,h,posi;
	int temp0,temp1,temp2;
    if(id==0){
        matrixpool=(float *)malloc(sizeof(float)*N*N);
    }
    //先将分散的C矩阵收集到一起
    MPI_Gather(source_c,num*num,MPI_FLOAT,matrixpool,num*num,MPI_FLOAT,0,MPI_COMM_CART);
    if(id==0){
        posi=0;
        for(i=0;i<part;i++)
            for(j=0,temp0=i*num;j<part;j++)
                for(h=0,temp1=j*num;h<num;h++)
                    for(w=0,temp2=(temp0+h)*N;w<num;w++)
                        target_c[temp2+temp1+w]=matrixpool[posi++];
        free(matrixpool);
    }
}
void Matrix_col_scatter(int my_id,float *source_matrix,float *target_matrix,int dims,int col,int count_p,MPI_Comm comm){
    float *matrix;
    int i,j,k,posi;
    int temp0,temp1;
    //将A矩阵先存储到连续的空间中再进行分发
    if(my_id==0){
        matrix=(float *)malloc(sizeof(float)*dims*dims);
        posi=0;
        for(i=0;i<count_p;i++)
            for(j=0,temp0=i*col;j<dims;j++)
                for(k=0,temp1=j*dims;k<col;k++)
                    matrix[posi++]=source_matrix[temp0+temp1+k];
    }
    MPI_Scatter(matrix,dims*col,MPI_FLOAT,target_matrix,dims*col,MPI_FLOAT,0,comm);
    if(my_id==0){
        free(matrix);
    }
}
void Print_matrix(float *matrix,int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%lf ",matrix[i*n+j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}
void Verify_matrix_c(float *A,float * B,float *C,int m1,int n1,int n2){
    float *matrixPool;
    int i;
    matrixPool=(float *)malloc(sizeof(float)*m1*n2);
    Init_Matrix(matrixPool,m1*n2,1);
    Mul_Matrix(A,B,matrixPool,m1,n1,n2);
    for(i=0;i<m1*n2;i++){
        if(C[i]!=matrixPool[i]){
            printf("计算结果错误!\n");
            if(m1*n2<=36){
                printf("A:\n");
                Print_matrix(A,m1,n1);
                printf("B:\n");
                Print_matrix(B,n1,n2);
                printf("C:\n");
                Print_matrix(C,m1,n2);
                printf("real-C:\n");
                Print_matrix(matrixPool,m1,n2);
            }
            return;
        }
    }
    printf("计算结果正确!\n");
}
#endif