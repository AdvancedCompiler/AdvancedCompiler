#include<stdio.h>
#include<mpi.h>
#include"mympi.h"
#define DIMS 1000
int main(int argc, char *argv[]){
    data_t *A,*B,*C;
    int world_rank, world_size,lens,i;
    double start_time, end_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if(DIMS%world_size!=0){
        printf("总进程数world_size应整除矩阵维数DIMS!!!\n");
        MPI_Finalize();
        return 0;
    }
    //为所有进程创建A、B、C的空间并初始化C
    //在0进程初始化A、B进程
    A=malloc(sizeof(data_t)*DIMS*DIMS);
    B=malloc(sizeof(data_t)*DIMS*DIMS);
    C=malloc(sizeof(data_t)*DIMS*DIMS);
    Init_Matrix(C,DIMS*DIMS,1);
    if(world_rank==0){
        Init_Matrix(A,DIMS*DIMS,2);
        Init_Matrix(B,DIMS*DIMS,2);
    }
    start_time=MPI_Wtime();
    //广播矩阵A、B到其他所有进程
    MPI_Bcast(A,DIMS*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    MPI_Bcast(B,DIMS*DIMS,MPI_FLOAT,0,MPI_COMM_WORLD);
    //每个矩阵要处理的A的行数
    lens = DIMS/world_size;
    //将A对应行与B相乘，结果存于C对应行
    Mul_Matrix(A+lens*DIMS*world_rank,B,C+lens*DIMS*world_rank,lens,DIMS,DIMS);
    //各进程将自身计算的C广播到其他进程，组合成完整的C
    for(i=0;i<world_size;i++){
        MPI_Bcast(C+i*lens*DIMS,lens*DIMS,MPI_FLOAT,i,MPI_COMM_WORLD);
    }
    end_time=MPI_Wtime();
    printf("进程%d的运行时间为:%lf\n",world_rank,(end_time-start_time));
    free(A);
    free(B);
    free(C);
    MPI_Finalize();
    return 0;
}