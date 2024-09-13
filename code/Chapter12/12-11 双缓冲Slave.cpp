#include<stdio.h>
#include"slave.h"
#include<stdlib.h>
#include"mympi.h"
#define I 1000
#define J 100
#define ROW_NUM 10
extern float *A;
extern float *B;
extern float *C;
extern float *tempA;
extern float *tempC;
__thread_local int my_id;
__thread_local volatile unsigned long get_reply[2],put_reply;\\注意get_reply[2]
__thread_local float local_A[J],local_A_buffer[J];\\开辟另一块空间，与local_A互为缓冲区
__thread_local float local_B[J*J];
__thread_local float local_C[J];
__thread_local float *slave[2];//设置指针数组，用于转换计算数组与接收数据数组的身份
void Mul_Matrix(){
        float temp; 
        int index,next;
        slave[0]=&local_A[0];
        slave[1]=&local_A_buffer[0];
        my_id=athread_get_id(-1);
        get_reply[0]=0;
	    athread_get(PE_MODE,&B[0],&local_B[0],4*J*J,&get_reply[0],0,0,0); 
	   //传输第一轮数据，需等待传输完成，get_reply修改置位。
		athread_get(PE_MODE,&tempA[my_id*ROW_NUM*J],&local_A[0],4*J,&get_reply[0],0,0,0);
        while(get_reply[0]!=2);
        for(int m=0;m<ROW_NUM;m++){
                index=m%2;
                next=(m+1)%2;
		   		get_reply[next]=0;
                //在传输next轮数据时，无需等待get_reply，开始上一轮次的计算
				athread_get(PE_MODE,&tempA[my_id*ROW_NUM*J+J*(m+1)],slave[next],4*J,&get_reply[next],0,0,0);
                for(int k=0;k<J;k++){
                        temp=0.0;
                        for(int l=0;l<J;l++){
                                temp=temp+(*(slave[index]+l))*local_B[k+l*J];//注意解指针的用法。
                        }
                        local_C[k]=temp;
                }
                while(get_reply[next]!=1);
	            put_reply=0; 
		    	athread_put(PE_MODE,&local_C[0],&tempC[my_id*ROW_NUM*J+J*m],J*4,&put_reply,0,0);
                while(put_reply!=1);
                }
}

