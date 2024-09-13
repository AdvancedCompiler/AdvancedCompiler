#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<immintrin.h>
#include"mympi.h"
#define DIMS 1000
void Mul_Matrix(float *A,float *B,float *C,int m1,int n1,int n2);//m1*n1维的A和n1*n2维的B相乘，存于m1*n2维的C中
void Verify_matrix_c(float *A,float * B,float *C,int m1,int n1,int n2);
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
    if(part*part!=p){//如果进程数不是平方数，则终止进程
        printf("总进程数必须是一个平方数!\n");
        MPI_Finalize();
        return 0;
    }
    if(DIMS%p!=0){//如果行数不是进程数的整数倍
        printf("总进程数开方之后必须能整除矩阵总行数!\n");
        MPI_Finalize();
        return 0;
    }
    num = DIMS/part;//建立笛卡尔通信域
    size[0] = size[1] = part;//虚拟拓扑维数
    periodic[0] = periodic[1] = 1;//虚拟拓扑中进程下标是否循环
    MPI_Cart_create(MPI_COMM_WORLD, 2, size, periodic, 1, &MPI_COMM_CART);
    MPI_Comm_rank(MPI_COMM_CART,&id);
    MPI_Cart_coords(MPI_COMM_CART,id,2,coord);
    x = coord[0];
    y = coord[1];
    a = (float*)malloc(sizeof(float)*num*num);  //为各个进程分配对应部分块矩阵的空间
    b = (float*)malloc(sizeof(float)*num*num);
    c = (float*)malloc(sizeof(float)*num*num);
    if (id==0){
        A = (float *)malloc(sizeof(float)*DIMS*DIMS);
        B = (float *)malloc(sizeof(float)*DIMS*DIMS);
        C = (float *)malloc(sizeof(float)*DIMS*DIMS);
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
    }
    start_time = MPI_Wtime();
    Matrix_cannon_scatter(DIMS,id,num,part,A,a,MPI_COMM_CART);  //分发矩阵
    Matrix_cannon_scatter(DIMS,id,num,part,B,b,MPI_COMM_CART);
    Init_Matrix(c,num*num,1);
    MPI_Cart_shift(MPI_COMM_CART, 1, x, &leftRank, &rightRank);//进行第一次循环位移 //获得当前矩阵块横坐标方向相聚x的左右方向的邻居进程号 //分块a循环左移x位
    MPI_Sendrecv_replace(a, num*num, MPI_FLOAT, leftRank, 0, rightRank, 0, MPI_COMM_CART, &status);
    MPI_Cart_shift(MPI_COMM_CART, 0, y, &upRank, &downRank);//获得当前矩阵块纵坐标方向相聚y的上下邻居进程号//分块b循环上移y位
    MPI_Sendrecv_replace(b, num*num, MPI_FLOAT, upRank, 0, downRank, 0, MPI_COMM_CART, &status);
    
    MPI_Cart_shift(MPI_COMM_CART, 0, 1, &upRank, &downRank);//获取上下左右相邻进程的进程号
    MPI_Cart_shift(MPI_COMM_CART, 1, 1, &leftRank, &rightRank);
    for (i = 0; i < part; ++i){//进行余下part次循环位移，并计算分块c
        Mul_Matrix(a,b,c,num,num,num);//每次计算得到的c都会和原有的c对应相加
        MPI_Sendrecv_replace(a, num*num, MPI_FLOAT, leftRank, 0, rightRank, 0, MPI_COMM_CART, &status);
        MPI_Sendrecv_replace(b, num*num, MPI_FLOAT, upRank, 0, downRank, 0, MPI_COMM_CART, &status);
    }
    Matrix_cannon_gather(DIMS,id,num,part,c,C,MPI_COMM_CART);//收集矩阵C
    end_time = MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",id,(end_time-start_time));
    MPI_Comm_free(&MPI_COMM_CART);
	if (id==0){
	  /*
	  printf("A:\n");
        Print_matrix(A,DIMS,DIMS);
	  printf("B:\n");
	  Print_matrix(B,DIMS,DIMS);
	  printf("C:\n");
	  Print_matrix(C,DIMS,DIMS);
          */
	  /*Verify_matrix_c(A,B,C,DIMS,DIMS,DIMS);*/
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
void Mul_Matrix(float *A,float *B,float *C,int m1,int n1,int n2){
	__m512 v1, v2, v3, v4;
	int k_max = n2 - n2 % 16;
	#pragma omp parallel for private(v1,v2,v3,v4) num_threads(8)
	for(int i=0;i<m1;i++){
		v4 = _mm512_setzero_ps();
		for(int j=0;j<n1;j++){
			v1 = _mm512_set1_ps(A[i*n1+j]);
			for(int k=0;k<k_max;k+=16){
				v2 = _mm512_loadu_ps(&B[j*n2+k]);
               				v3 = _mm512_loadu_ps(&C[i*n2+k]);
				v4 = _mm512_fmadd_ps(v1,v2,v3);
				_mm512_storeu_ps(&C[i*n2+k],v4);
			}
			for(int k=k_max;k<n2;k++){
				C[i*n2+k]+=A[i*n1+j]*B[j*n2+k];
			}
		}
	}
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
