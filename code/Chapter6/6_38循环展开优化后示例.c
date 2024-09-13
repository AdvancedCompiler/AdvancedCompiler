#include <stdio.h>
int main() {
    const int N = 256;
    float A[N][N], B[N][N], C[N][N];
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
            C[i][j] = 3.0;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j += 4) {
            A[i][j] = A[i][j] + B[i][j] * C[i][j];
            A[i][j + 1] = A[i][j + 1] + B[i][j + 1] * C[i][j + 1];
            A[i][j + 2] = A[i][j + 2] + B[i][j + 2] * C[i][j + 2];
            A[i][j + 3] = A[i][j + 3] + B[i][j + 3] * C[i][j + 3];
        }
        for (j=(N / 4) * 4 + 1; j < N; j++)	//尾部循环
            A[i][j] = A[i][j] + B[i][j] * C[i][j];
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%lf  ", A[i][j]);
        }
        printf("\n");
    }
}