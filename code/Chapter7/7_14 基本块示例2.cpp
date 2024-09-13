#include <stdio.h>
#include <stdlib.h>
#define N 4
float C[N],B[N];

int main(){

	int i,j;
	for(i=0;i<N;i++){
		C[i]=i*2;
		printf("%f  ",C[i]);
	}
	printf("\n");
	for(i=0;i<N;i++){
		B[i]=i/2;
		printf("%f  ",B[i]);
	}
	printf("\n");
//非同构
	for(i=0;i<N;i+=2){
		C[i]=B[i]*0.5+2;
		C[i+1]=B[i+1] + 1;
	}

	for(i=0;i<N;i++){
		printf("%f ",C[i]);
	}
	printf("\n");
//同构	
	for(i=0;i<N;i+=2){
		C[i]=B[i]*0.5+2;
		C[i+1]=B[i+1]*1+1;
	}

	for(i=0;i<N;i++){
		printf("%f ",C[i]);
	}
	printf("\n");

return 0;

} 

