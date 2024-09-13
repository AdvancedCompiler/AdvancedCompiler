#include <stdio.h>
#include <stdlib.h>
#define N 10
int main(){
	int a[N];
	for(int i = 0; i < N; i++)
	{
		a[i] = 0;
	}
	int C0=1;
	int C1=2;
	for(int i=0; i<N; i++)
	{
		a[i]=(i*2>2)?C0:C1;	
	}
	for(int i=0; i<N; i++)
	{
		printf("a[%d]=%d\n",i,a[i]);
	}
return 0;	
}
