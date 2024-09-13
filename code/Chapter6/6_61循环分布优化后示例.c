#include <stdio.h>
int main() {
    int N = 256;
    float A[N][N], B[N][N], C[N][N], D;
    int i, j, k;
    D = 4.0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
            C[i][j] = 3.0;
        }
    }
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = D;//S1语句
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                A[i][j] = A[i][j] + B[i][k] * C[k][j];//S2语句                                                                                                                                                                                                          
}