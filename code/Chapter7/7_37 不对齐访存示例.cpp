#include <stdio.h>
#include <immintrin.h>
#define N 100
float A[N+2],C[N];
int main(){
	for(int i=0;i<N+2;i++)
		A[i]=i;
	for(int i=0;i<N;i+=4){
	__m128 va=_mm_loadu_ps(&A[i+2]);
	_mm_storeu_ps(&C[i],va);
}
		
	for(int i=0;i<N;i++){
		printf("%f ",C[i]);
	}
		printf("\n");

	return 0;
}
