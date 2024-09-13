#include <stdio.h>
#include <stdlib.h>
#define N 4
float A[N],C[N],B[N],D[N];

int main(){

	int i,j;
	float a0=3;
	float a1=2;
	for(i=0;i<N;i++){
		B[i]=i*2;
		printf("%f  ",B[i]);
	}
	printf("\n");
	for(i=0;i<N;i++){
		A[i]=i+2;
		D[i]=i-1;
		printf("%f  %f  ,",A[i],D[i]);
	}
	printf("\n");
//非同构
	for(i=0;i<N;i+=2){
		C[i]=B[i]*0.5+ a0 + A[i]-D[i];
		C[i+1]=B[i+1]*0.5 + a1;
	}

	for(i=0;i<N;i++){
		printf("%f ",C[i]);
	}
	printf("\n");
//同构	
	int a2=a0;
	for(i=0;i<N;i+=2){
		a0=a2+A[i]-D[i];
		C[i]=B[i]*0.5+ a0;
		C[i+1]=B[i+1]*0.5 + a1;
	}

	for(i=0;i<N;i++){
		printf("%f ",C[i]);
	}
	printf("\n");

return 0;

} 

