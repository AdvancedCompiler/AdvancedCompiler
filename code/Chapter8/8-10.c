#include <stdio.h>
#define N 8
int main() {
    float A[N][N];
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
        }
    }
    for (i = 1; i < N-1; i++)
        for (j = 1; j < N-1; j++)
        A[i][j+1] = A[i+1][j]+1;//语句S
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f  ",A[i][j]);
        }
    }
}