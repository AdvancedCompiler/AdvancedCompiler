#include <stdio.h>
#define N 100
int main()
{
    int Vec[N];
    int i, M = 50;
    for (i = 0; i < N; i++) {
        Vec[i] = i;
    }
    for (i = 1; i < M; i++)
        Vec[i] = Vec[i] + Vec[M];
    for (i = M + 1; i < N; i++)
        Vec[i] = Vec[i] + Vec[M];
    printf("进行循环分裂变换，得到两个循环就方便循环向量化\n");
    return 0;
}