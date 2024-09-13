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
    for (j = 0; j < N; j++)
        for (k = 0; k < N; k++)
            for (i = 0; i < N; i++)
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
}