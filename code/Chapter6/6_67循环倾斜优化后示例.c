#include <stdio.h>
#define N 8
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
int main() {
    float A[N][N];
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
        }
    }
    for (j = 2; j < 2 * N; j++)
        for (i = max(1,j-N); i < min(N,j); i++)
            A[i][j - i] = A[i - 1][j - i] + A[i][j - i - 1];
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f  ", A[i][j]);
        }
    }
}