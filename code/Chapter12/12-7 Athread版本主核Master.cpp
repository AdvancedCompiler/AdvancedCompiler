//���˴���Master.c
#include<stdlib.h>

#include<athread.h>
#define J 100//���������Զ��壬ע������ģ��С��Ҫ���ھִ��С���ɡ�
#define I 100//���������Զ���
float matrix_a[I*J];//����A
float matrix_b[I*J];//����B
float matrix_c[I*J];//����C���洢A��B�Ľ��
extern SLAVE_FUN(Mul_Matrix)();//���������ڴӺ�slave.c�ϵ��ⲿ����
int main(void){
	Init_Matrix(matrix_a,I*J,10);//�Ը�������г�ʼ������ͬ
	Init_Matrix(matrix_b,I*J,10);
	Init_Matrix(matrix_c,I*J,10);
	athread_init();
	athread_spawn(Mul_Matrix,0);//Mul_MatrixΪ�����ڴӺ��ϵļ������
	athread_join();
	athread_halt();
	return 0;
}

