#include<stdio.h>
#include"slave.h"
#include<stdlib.h>
#define I 100
#define J 100
#define ROW_NUM 100 //每个从核所分得的所需计算的矩阵行数
extern float *A，*B，*C;
extern float *tempA，*tempC;
__thread_local int my_id;
__thread_local volatile unsigned long get_reply,put_reply;
__thread_local float local_A[I];
__thread_local float local_B[I*J];
__thread_local float local_C[I];
void Mul_Matrix(){
	int temp; 
	my_id=athread_get_id(-1);
	get_reply=0;
	athread_get(PE_MODE,&B[0],&local_B[0],4*I*J,&get_reply,0,0,0);
	while(get_reply!=1);
	for(int i=0;i<ROW_NUM;i++){
		get_reply=0;
		athread_get(PE_MODE,&tempA[my_id*ROW_NUM*J+J*i],&local_A[0],4*J,\
		&get_reply,0,0,0);
		while(get_reply!=1);
		for(int k=0;k<J;k++){
			float temp=0.0;
			for(int l=0;l<J;l++){
				temp=temp+local_A[l]*local_B[k+l*J];
			}
			local_C[k]=temp;
		}
		put_reply=0;
		athread_put(PE_MODE,&local_C[0],&tempC[my_id*J*i+J*i],I*4,&put_reply,0,0);
		while(put_reply!=1);
	}
}

