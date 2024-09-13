#include <stdio.h>
int main() {
    const int N = 2;
    const int M = 8;
    const int L = 8;
    float A[N][M][L], B[N][M][L];
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            for (k = 0; k < L; k++) {
                A[i][j][k] = 1.0;
                B[i][j][k] = 2.0;
            }
        }
    }
    for (i = 1; i < N; i++) {
        for (j = 1; j < M; j++) {
            for (k = 0; k < L; k++) {
                A[i][j][k] = A[i][j - 1][k] + A[i - 1][j][k];
                B[i][j][k + 1] = B[i][j][k] + A[i][j][k];
            }
        }
    }
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            for (k = 0; k < L; k++)
                printf("%f  ", A[i][j][k]);
}