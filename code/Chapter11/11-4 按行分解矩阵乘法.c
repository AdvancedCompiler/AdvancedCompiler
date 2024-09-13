#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include"mympi.h"
#define DIMS 1000
int main(int argc, char *argv[]){
    data_t *A,*B,*C,*tempA,*tempC;
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
    //为所有进程创建B的空间并在0进程进行初始化
    B=malloc(sizeof(data_t)*DIMS*DIMS);
    if(world_rank==0){
        A=malloc(sizeof(data_t)*DIMS*DIMS);
        C=malloc(sizeof(data_t)*DIMS*DIMS);
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
        Init_Matrix(C,DIMS*DIMS,1);
    }
    start_time=MPI_Wtime();
    //广播矩阵B到其他所有进程
    MPI_Bcast(B,DIMS*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    lens = DIMS/world_size;//每个矩阵要处理的A行数
    //根据要处理的数据大小申请空间并分发数据
    tempA=malloc(sizeof(data_t)*lens*DIMS);
    tempC=malloc(sizeof(data_t)*lens*DIMS);
    //0进程分发A的不同行到其他所有进程
MPI_Scatter(A,lens*DIMS,MPI_FLOAT,tempA,lens*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    //计算各自的矩阵乘并将结果发送给0进程
    Mul_Matrix(tempA,B,tempC,lens,DIMS,DIMS);
MPI_Gather(tempC,lens*DIMS,MPI_FLOAT,C,lens*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    end_time=MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",world_rank,(end_time-start_time));
    if(world_rank==0){
        free(A);
        free(C);
    }
    free(B);
    free(tempA);
    free(tempC);
    MPI_Finalize();
    return 0;
}