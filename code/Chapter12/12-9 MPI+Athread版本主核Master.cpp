#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
#include"mympi.h"
#include<athread.h>
#define I 100//定义矩阵的维数，可自定义
#define J 100
float * A,* B,* C;//声明矩阵A、B、C
float *tempA,*tempC;//声明tempA和tempC，存A分发的几行数据和C的几行结果
extern SLAVE_FUN(Mul_Matrix)();
int main(int argc,char **argv){
	int id;//进程号	
	int p;//进程数
	int count;//每个进程要处理的矩阵A的行数
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	B=(int *)malloc(I*J*sizeof(float));
	//进程0负责对各矩阵进行初始化
	if(id==0){
		A=(float *)malloc(I*J*sizeof(float));
		C=(float *)malloc(I*J*sizeof(float));
		Init_Matrix(A,I*J,10);
		Init_Matrix(B,I*J,10);
		Init_Matrix(C,I*J,1);
	}
	MPI_Bcast(B,I*J,MPI_FLOAT,0,MPI_COMM_WORLD);//进程0广播B至各进程
	count=I/p;//每个进程所分得的行数
	tempA=(float *)malloc(count*J*sizeof(float));
	tempC=(float *)malloc(count*J*sizeof(float));
	MPI_Scatter(A,count*J,MPI_FLOAT,tempA,count*J,MPI_FLOAT,0,MPI_COMM_WORLD);
	athread_init();//开始利用从核组对某进程分得的部分矩阵进行计算
	athread_spawn(Mul_Matrix,0);
	athread_join();
	athread_halt();
	//收集各进程的结果至进程0
	MPI_Gather(tempC,count*J,MPI_FLOAT,C,count*J,MPI_FLOAT,0,MPI_COMM_WORLD);
	free(B);
	free(tempA);
	free(tempC);
	return 0;
}

