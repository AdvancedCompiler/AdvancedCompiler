//主核代码Master.c
#include<stdlib.h>

#include<athread.h>
#define J 100//列数，可自定义，注意矩阵规模大小不要大于局存大小即可。
#define I 100//行数，可自定义
float matrix_a[I*J];//矩阵A
float matrix_b[I*J];//矩阵B
float matrix_c[I*J];//矩阵C，存储A×B的结果
extern SLAVE_FUN(Mul_Matrix)();//引入运行在从核slave.c上的外部函数
int main(void){
	Init_Matrix(matrix_a,I*J,10);//对各矩阵进行初始化，下同
	Init_Matrix(matrix_b,I*J,10);
	Init_Matrix(matrix_c,I*J,10);
	athread_init();
	athread_spawn(Mul_Matrix,0);//Mul_Matrix为运行在从核上的计算程序
	athread_join();
	athread_halt();
	return 0;
}

