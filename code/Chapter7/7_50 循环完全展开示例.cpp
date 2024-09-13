#include <stdio.h>
#define N 8

int main(){
	float A[N],B[N];
	for(int i=0;i<N;i++)
		A[i]=i*2;

	for(int i=0;i<N;i++)
		B[i]=A[i];
	printf("B:\n");	
	for(int i=0;i<N;i++)
		printf("%f  ",B[i]);
	printf("\n");	
	return 0;
}
