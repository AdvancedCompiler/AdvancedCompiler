//�Ӻ˴�������
#include<stdio.h>
#include<stdlib.h>
#include"slave.h"
#define J 100
#define I 100
#define ROW_NUM 64 //�Ӻ˷ֵ�������������
__thread_local float my_id;//�̺߳ţ�ע�⣬�������»��ߣ�
__thread_local float local_A[I];/�Ӻ˾ִ����ݴ������ȡ����a�����ĳһ��
__thread_local float local_B[I*J];//�������մ�����ȡ���ľ���b 
__thread_local volatile float local_C[I];//�����ݴ������ĳһ�У������������c��
extern float matrix_a[I*J],matrix_b[I*J],matrix_c[I*J];//�����ⲿ�����ķ�ʽ���������ַ
__thread_local volatile unsigned long get_reply,put_reply;//����DMA����ʱ�ı�־λ
void Mul_Matrix(){
	float temp; //���ڼ��㣬�ݴ�ĳ����Ԫ�صĽ��
	my_id=athread_get_id(-1); //��ȡ�Ӻ��߼�id��
	get_reply=0;//��ȡ����ʱ�ı�־λ
	put_reply=0;//��������ʱ�ı�־λ
	//�������ж�ȡ��������B���Ӻ˾ִ��matr_b��
	athread_get(PE_MODE,&matrix_b[0],&local_B[0],I*J*4,&get_reply,0,0,0);
	while(get_reply!=1);
	//���δ������ж�ȡ����A��ĳһ�����ݴ���Ӻ˾ִ�local_A��
	for(int i=0;i<ROW_NUM;i++){
		get_reply=0;
		athread_get(PE_MODE,&matrix_a[my_id*ROW_NUM*J+*J*i],&local_A[0],J*4,\
		&get_reply,0,0,0);
		while(get_reply!=1);//�ȴ��������		
		//��ʼ����C��ĳһ�е�����
		for(int k=0;k<J;k++){
			int temp=0;
			for(int l=0;l<J;l++){
				temp=temp+local_A[l]*local_B[k+l*J];
			}
			local_C[k]=temp;
		}
		//��������ɵ�ĳһ�е����ݴ���������е�ָ��λ�á�
		athread_put(PE_MODE,&local_C[0],&matrix_c[my_id*J*i],J*4,&put_reply,0,0);
		while(put_reply!= 1);//�ȴ��������
		put_reply=0;
}

