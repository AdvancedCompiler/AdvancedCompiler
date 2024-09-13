//从核代码如下
#include<stdio.h>
#include<stdlib.h>
#include"slave.h"
#define J 100
#define I 100
#define ROW_NUM 64 //从核分得所需计算的行数
__thread_local float my_id;//线程号，注意，是两个下划线！
__thread_local float local_A[I];/从核局存上暂存从主存取来的a矩阵的某一行
__thread_local float local_B[I*J];//用来接收从主存取来的矩阵b 
__thread_local volatile float local_C[I];//用来暂存计算后的某一行，传回主存矩阵c中
extern float matrix_a[I*J],matrix_b[I*J],matrix_c[I*J];//引用外部变量的方式访问主存地址
__thread_local volatile unsigned long get_reply,put_reply;//用于DMA传输时的标志位
void Mul_Matrix(){
	float temp; //用于计算，暂存某矩阵元素的结果
	my_id=athread_get_id(-1); //获取从核逻辑id号
	get_reply=0;//读取数据时的标志位
	put_reply=0;//返回数据时的标志位
	//从主存中读取完整矩阵B到从核局存的matr_b中
	athread_get(PE_MODE,&matrix_b[0],&local_B[0],I*J*4,&get_reply,0,0,0);
	while(get_reply!=1);
	//依次从主存中读取矩阵A的某一行数据存入从核局存local_A中
	for(int i=0;i<ROW_NUM;i++){
		get_reply=0;
		athread_get(PE_MODE,&matrix_a[my_id*ROW_NUM*J+*J*i],&local_A[0],J*4,\
		&get_reply,0,0,0);
		while(get_reply!=1);//等待传输完成		
		//开始计算C的某一行的数据
		for(int k=0;k<J;k++){
			int temp=0;
			for(int l=0;l<J;l++){
				temp=temp+local_A[l]*local_B[k+l*J];
			}
			local_C[k]=temp;
		}
		//将计算完成的某一行的数据传输回主存中的指定位置。
		athread_put(PE_MODE,&local_C[0],&matrix_c[my_id*J*i],J*4,&put_reply,0,0);
		while(put_reply!= 1);//等待传输完成
		put_reply=0;
}

