#include <stdio.h>
#include <x86intrin.h>
#define N 128 
int main() {
    __m128 ymm0, ymm1, ymm2;
    float A[N], B[N], C, D;
    C = 5;
    D = 6;
    int i;
    for (i = 0; i < N; i++) {
        A[i] = 1;
        B[i] = 2;
    }
    for (i = 0; i < N; i++)
        A[i + 1] = A[i] + C;
    ymm0 = _mm_set_ps(D, D, D, D);
    for (i = 0; i < N / 4; i++) {
        ymm1 = _mm_load_ps(B + 4 * i);
        ymm2 = _mm_add_ps(ymm0, ymm1);
        _mm_storeu_ps(B + 4 * i, ymm2);
    }
}