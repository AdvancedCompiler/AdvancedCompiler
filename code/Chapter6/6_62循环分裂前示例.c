#include <stdio.h>
#define N 100
int main()
{
    int Vec[N];
    int i, M = 50;
    for (i = 0; i < N; i++) {
        Vec[i] = i;
    }
    for (i = 1; i < N; i++)
        Vec[i] = Vec[i] + Vec[M];
    printf("由于M，该循环含有可能阻碍向量化的依赖关系\n");
    return 0;
}