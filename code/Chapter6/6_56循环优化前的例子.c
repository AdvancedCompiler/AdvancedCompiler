#include <stdio.h>
#include<time.h>
int main() {
    const int M=1000,N=1000;
    double Total_time;
    clock_t start, end;
    int i, j;
    float A[N][N];
    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            A[i][j] = j;
    start = clock();
    for (i = 1; j < M; j++)
        for (j = 1; i < N; i++)
            A[i][j] = A[i - 1][j];
    end = clock();
    Total_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("进行循环交换优化前：%lf秒\n", Total_time);
}