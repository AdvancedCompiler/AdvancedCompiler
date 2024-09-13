#include <stdio.h>
#define N 100
float A[N+2],C[N];
int main(){
	for(int i=0;i<N+2;i++)
		A[i]=i;
	for(int i=0;i<N;i++)
		C[i]=A[i+2];
	for(int i=0;i<N;i++){
		printf("%f ",C[i]);
	}
		printf("\n");

	return 0;
}
