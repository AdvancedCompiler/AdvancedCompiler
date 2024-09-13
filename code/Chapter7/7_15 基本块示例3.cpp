#include <stdio.h>
#include <stdlib.h>
#define N 4
struct plu{
	float real;
	float imag;
};
plu A[N],B[N],C[N];

int main(){

	int i;
	for(i=0;i<N;i++){
		A[i].real=i*2;
		A[i].imag=i*3;
		printf("%f  %f  ,",A[i].real,A[i].imag);
	}
	printf("\n");
	for(i=0;i<N;i++){
		B[i].real=i-1;
		B[i].imag=i-2;
		printf("%f  %f ,",B[i].real,B[i].imag);
	}
	printf("\n");

	for(i=0;i<N;i++){
		C[i].real = (A[i].real - B[i].real)*0.5;
		C[i].imag = (A[i].imag + B[i].imag)*0.5;
	}

	for(i=0;i<N;i++){
		printf("%f  %f  ,",C[i].real,C[i].imag);
	}
	printf("\n");
	
	for(i=0;i<N;i++){
		C[i].real = (A[i].real +(-1)* B[i].real)*0.5;
		C[i].imag = (A[i].imag + 1*B[i].imag)*0.5;
	}

	for(i=0;i<N;i++){
		printf("%f  %f  ,",C[i].real,C[i].imag);
	}
	printf("\n");

return 0;

} 

