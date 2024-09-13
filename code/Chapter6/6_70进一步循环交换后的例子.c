#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
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
    for (k = 2; k < M + L; k++)
        for (i = max(1, k - M - L - 1); i < min(N, k + L - 2); i++)
            for (j = max(1, k - i - L); j < min(M, k + i - 1); j++) {
                A[i][j][k - i - j] = A[i][j - 1][k - i - j] + A[i - 1][j][k - i - j];
                B[i][j][k - i - j] = B[i][j][k - i - j] + A[i][j][k - i - j];
            }
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            for (k = 0; k < L; k++)
                printf("%f  ", A[i][j][k]);
}