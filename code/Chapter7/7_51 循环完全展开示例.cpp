#include <stdio.h>
#include <immintrin.h>
#define N 8

int main(){
	float A[N],B[N];
	for(int i=0;i<N;i++)
		A[i]=i*2;

	__m128 v1=_mm_load_ps(&A[0]);
	_mm_store_ps(&B[0],v1);
	v1=_mm_load_ps(&A[4]);
	_mm_store_ps(&B[4],v1);

	printf("B:\n");	
	for(int i=0;i<N;i++)
		printf("%f  ",B[i]);
	printf("\n");	
	return 0;
}
