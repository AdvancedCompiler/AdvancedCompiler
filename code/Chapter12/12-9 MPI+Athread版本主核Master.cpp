#include<stdio.h>
#include<stdlib.h>
#include"mpi.h"
#include"mympi.h"
#include<athread.h>
#define I 100//��������ά�������Զ���
#define J 100
float * A,* B,* C;//��������A��B��C
float *tempA,*tempC;//����tempA��tempC����A�ַ��ļ������ݺ�C�ļ��н��
extern SLAVE_FUN(Mul_Matrix)();
int main(int argc,char **argv){
	int id;//���̺�	
	int p;//������
	int count;//ÿ������Ҫ����ľ���A������
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	B=(int *)malloc(I*J*sizeof(float));
	//����0����Ը�������г�ʼ��
	if(id==0){
		A=(float *)malloc(I*J*sizeof(float));
		C=(float *)malloc(I*J*sizeof(float));
		Init_Matrix(A,I*J,10);
		Init_Matrix(B,I*J,10);
		Init_Matrix(C,I*J,1);
	}
	MPI_Bcast(B,I*J,MPI_FLOAT,0,MPI_COMM_WORLD);//����0�㲥B��������
	count=I/p;//ÿ���������ֵõ�����
	tempA=(float *)malloc(count*J*sizeof(float));
	tempC=(float *)malloc(count*J*sizeof(float));
	MPI_Scatter(A,count*J,MPI_FLOAT,tempA,count*J,MPI_FLOAT,0,MPI_COMM_WORLD);
	athread_init();//��ʼ���ôӺ����ĳ���̷ֵõĲ��־�����м���
	athread_spawn(Mul_Matrix,0);
	athread_join();
	athread_halt();
	//�ռ������̵Ľ��������0
	MPI_Gather(tempC,count*J,MPI_FLOAT,C,count*J,MPI_FLOAT,0,MPI_COMM_WORLD);
	free(B);
	free(tempA);
	free(tempC);
	return 0;
}

