#include <stdio.h>
int main() {
    int N = 8;
    float A[N][N];
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
        }
    }
    for (i = 1; i < N; i++)
        for (j = 1; j < N; j++)
            A[i][j] = A[i - 1][j] + A[i][j - 1];//S语句 
}