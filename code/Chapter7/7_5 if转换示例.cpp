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
		if(i*2>2)
		{
			a[i]=C0;
		}
		else
		{
			a[i]=C1;
		}
	}
	for(int i=0; i<N; i++)
	{
		printf("a[%d]=%d\n",i,a[i]);
	}
return 0;

}
