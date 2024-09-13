#include <stdio.h>
#include <immintrin.h>
#define N 256
int main() {
    float A[N][N], B[N][N], C[N][N];
    int i, j, k;
    __m128 VA, VB, VC;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
            C[i][j] = 3.0;
        }
    }
    for (k = 0; k < N; k += 4) {
        for (j = 0; j < N; j += 4) {
            VC = _mm_loadu_ps(C[k, j]);
            for (i = 0; i < N; i += 4) {
                VA = _mm_loadu_ps(A[i, j]);
                VB = _mm_loadu_ps(B[i, k]);
                VB = _mm_mul_ps(VB, VC);
                VA = _mm_add_ps(VA, VB);
                _mm_storeu_ps(A[i, j], VA);
            }
        }
    }
}