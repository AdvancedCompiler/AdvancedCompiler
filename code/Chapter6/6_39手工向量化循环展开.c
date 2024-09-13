#include <stdio.h>
#include <x86intrin.h>
int main() {
    __m256 ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6;
    const int N = 256;
    double A[N][N], B[N][N], C[N][N], D[N][N];
    double d[4] = { 1,1,1,1 };
    double e[4] = { 2,2,2,2 };
    double f[4] = { 3,3,3,3 };
    int block = N / 4;
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < block; j++) {
            ymm0 = _mm256_loadu_pd(d);
            ymm1 = _mm256_loadu_pd(e);
            ymm2 = _mm256_loadu_pd(f);
            _mm256_storeu_pd(A[i] + 4 * j, ymm0);
            _mm256_storeu_pd(B[i] + 4 * j, ymm1);
            _mm256_storeu_pd(C[i] + 4 * j, ymm2);
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < block; j++) {
            ymm3 = _mm256_loadu_pd(A[i] + 4 * j);
            ymm4 = _mm256_loadu_pd(B[i] + 4 * j);
            ymm5 = _mm256_loadu_pd(C[i] + 4 * j);
            ymm4 = _mm256_mul_pd(ymm4, ymm5);
            ymm6 = _mm256_add_pd(ymm3, ymm4);
            _mm256_storeu_pd(A[i] + 4 * j, ymm6);
        }
    }
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%lf  ", A[i][j]);
		}
		printf("\n");
	}
}