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
__thread_local volatile unsigned long get_reply[2],put_reply;\\ע��get_reply[2]
__thread_local float local_A[J],local_A_buffer[J];\\������һ��ռ䣬��local_A��Ϊ������
__thread_local float local_B[J*J];
__thread_local float local_C[J];
__thread_local float *slave[2];//����ָ�����飬����ת���������������������������
void Mul_Matrix(){
        float temp; 
        int index,next;
        slave[0]=&local_A[0];
        slave[1]=&local_A_buffer[0];
        my_id=athread_get_id(-1);
        get_reply[0]=0;
	    athread_get(PE_MODE,&B[0],&local_B[0],4*J*J,&get_reply[0],0,0,0); 
	   //�����һ�����ݣ���ȴ�������ɣ�get_reply�޸���λ��
		athread_get(PE_MODE,&tempA[my_id*ROW_NUM*J],&local_A[0],4*J,&get_reply[0],0,0,0);
        while(get_reply[0]!=2);
        for(int m=0;m<ROW_NUM;m++){
                index=m%2;
                next=(m+1)%2;
		   		get_reply[next]=0;
                //�ڴ���next������ʱ������ȴ�get_reply����ʼ��һ�ִεļ���
				athread_get(PE_MODE,&tempA[my_id*ROW_NUM*J+J*(m+1)],slave[next],4*J,&get_reply[next],0,0,0);
                for(int k=0;k<J;k++){
                        temp=0.0;
                        for(int l=0;l<J;l++){
                                temp=temp+(*(slave[index]+l))*local_B[k+l*J];//ע���ָ����÷���
                        }
                        local_C[k]=temp;
                }
                while(get_reply[next]!=1);
	            put_reply=0; 
		    	athread_put(PE_MODE,&local_C[0],&tempC[my_id*ROW_NUM*J+J*m],J*4,&put_reply,0,0);
                while(put_reply!=1);
                }
}

