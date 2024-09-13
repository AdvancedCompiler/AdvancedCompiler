#include<stdio.h>
#include"slave.h"
#include<stdlib.h>
#include"mympi.h"
#define I 1000
#define J 100
#define ROW_NUM 10
extern float *A,* B,* C; 
extern float *tempA,*tempC;
__thread_local int my_id;
__thread_local volatile unsigned long get_reply,put_reply;
__thread_local float local_A[ROW_NUM*J];
__thread_local float local_B[J*J];
__thread_local float local_C[ROW_NUM*J];
void Mul_Matrix(){
    int k,l;
    float temp; 
    my_id=athread_get_id(-1);
    get_reply=0;
    athread_get(PE_MODE,&B[0],&local_B[0],4*J*J,&get_reply,0,0,0);
	//注意，这里数据传输粒度大小发生变化，不再是一行元素了。
	athread_get(PE_MODE,&tempA[my_id*ROW_NUM*J],&local_A[0],4*ROW_NUM*J,&get_reply,0,0,0);
    while(get_reply!=2);
	Mul_Matrix(local_A,local_B,local_C,ROW_NUM,J,J);
	put_reply=0;   
    athread_put(PE_MODE,&local_C[0],&tempC[my_id*ROW_NUM*J],ROW_NUM*J*4,&put_reply,0,0);
	while(put_reply!=1);
}

