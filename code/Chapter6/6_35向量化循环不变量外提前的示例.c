#include<stdio.h>
#include<stdlib.h>
#include <immintrin.h>
#define N 16
void main() {
	float A[N], B[N];
	float C0 = 2.0;
	int i;
	__m128 v1, v2, v3;
	for (i = 0; i < N; i++) {
		B[i] = 1.0;
	}
	for (i = 0; i < N; i += 4) {
		v1 = _mm_loadu_ps(&B[i]);
		v2 = _mm_set_ps1(C0);
		v3 = _mm_mul_ps(v1, v2);
		_mm_store_ps(&A[i], v3);
	}
	for (i = 0; i < N; i++) {
		printf("%f  ", A[i]);
	}
}