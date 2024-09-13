#include<stdio.h>
#include<omp.h>
#define N 16
int main(){
int i,A[N];
#pragma omp parallel private(i)  num_threads(4)
{
	#pragma omp for 
	for(i=0;i<N;i++){
	A[i] = i;
	printf("thread id = %d : A[%d] = %d\n",omp_get_thread_num(),i,A[i]);
	}
	#pragma omp master
	printf("thread id = %d : All work done !\n",omp_get_thread_num());
}
}

