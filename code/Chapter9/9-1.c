#include<stdio.h>
#define N 16
int A[N],B[N],C[N];
int main(){
for(int i=0;i<N;i++)
{
	A[i] = i;
	B[i] = 1;
	C[i] = 0;
}
for(int j=0;j<N;j++)
{
	C[j] = A[j] + B[j];
	printf("thread id = 0 compute A[%d]+B[%d] = %d\n",j,j,C[j]);
}
}
