#include<stdio.h>
#include<omp.h>
#define N 16
int A[N],B[N],C[N];
int main(){
for(int i=0;i<N;i++)
{
	A[i] = i;
	B[i] = 1;
	C[i] = 0;
}
#pragma omp parallel for num_threads(4)
for(int j=0;j<N;j++)
{
	C[j] = A[j] + B[j];
	printf("thread id = %d compute A[%d]+B[%d] = %d\n",omp_get_thread_num(),j,j,C[j]);
}
}
