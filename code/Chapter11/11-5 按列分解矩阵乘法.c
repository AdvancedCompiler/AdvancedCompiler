#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include"mympi.h"
#define DIMS 1000
int main(int argc, char *argv[]){
    data_t *A,*B,*C,*tempA,*tempB,*tempC;
    int world_rank, world_size,lens;
    double start_time, end_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if(DIMS%world_size!=0){
        printf("总进程数world_size应整除矩阵维数DIMS!!!\n");
        MPI_Finalize();
        return 0;
    }
    if(world_rank==0){
        A=malloc(sizeof(data_t)*DIMS*DIMS);
        B=malloc(sizeof(data_t)*DIMS*DIMS);
        C=malloc(sizeof(data_t)*DIMS*DIMS);
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
        Init_Matrix(C,DIMS*DIMS,1);
    }
    start_time=MPI_Wtime();
    lens = DIMS/world_size;//每个矩阵要处理的A的列数以及B的行数
    tempA=malloc(sizeof(data_t)*lens*DIMS);
    tempB=malloc(sizeof(data_t)*lens*DIMS);
    tempC=malloc(sizeof(data_t)*DIMS*DIMS);
    //分配矩阵A、矩阵B到所有进程，并计算部分C
    Matrix_col_scatter(world_rank,A,tempA,DIMS,lens,world_size,MPI_COMM_WORLD);
    MPI_Scatter(B,lens*DIMS,MPI_FLOAT,tempB,lens*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    Mul_Matrix(tempA,tempB,tempC,DIMS,lens,DIMS);
    //对C进行规约操作。将所有tempC矩阵对应位置相加，结果存于C
    MPI_Reduce(tempC,C,DIMS*DIMS,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    end_time=MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",world_rank,(end_time-start_time));
    if(world_rank==0){
        int i,j;
        free(A);
        free(B);
        free(C);
    }
    free(tempA);
    free(tempB);
    free(tempC);
    MPI_Finalize();
    return 0;
}