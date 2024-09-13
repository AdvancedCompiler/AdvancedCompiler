#include <stdio.h>
#include<time.h>
#define MIN(a,b) ((a)<(b)?(a):(b))
int main() {
    const int N = 256;
    double Total_time;
    clock_t start, end;
    float A[N][N], B[N][N], C[N][N];
    int i, j, k, I;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 2.0;
            C[i][j] = 3.0;
        }
    }
    int S = 4;
    start = clock();
    for (i = 0; i < N; i += S)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                for (I = i; I < MIN(i + S - 1, N); I++)
                    C[I][j] = C[I][j] + A[I][k] * B[k][j];
    end = clock();
    Total_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("进行循环分块优化一后：%lf秒\n", Total_time);
}