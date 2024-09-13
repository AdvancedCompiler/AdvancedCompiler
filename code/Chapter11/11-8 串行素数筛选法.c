#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_PRIME 100000001
int main()
{
    int index, i;
    double start, end;
    char *prime;
    //先假设所有的都为素数
    prime = malloc(sizeof(char) * (MAX_PRIME));
    memset(prime, 'y', MAX_PRIME);
    //将0、1标记为非素数
    prime[0] = prime[1] = 'n';
    // 标记2的倍数
    for (i = 2; i < MAX_PRIME; i++)
    {
        if (i % 2 == 0)
        {
            prime[i] = 'n';
        }
    }
    prime[2] = 'y';
    start = (double)clock() / 1e6;
    index = 2;
    while (index * index <= MAX_PRIME)
    {
        //将index的倍数标记为非素数
        for (i = index * 2; i <= MAX_PRIME; i += index)
        {
            prime[i] = 'n';
        }
        //选择新的未标记数
        for (i = index + 1; i <= MAX_PRIME; i++)
        {
            if (prime[i] == 'y')
            {
                index = i;
                break;
            }
        }
    }
    end = (double)clock() / 1e6;
    printf("进程的执行时间为:%.2lfs\n", end - start);
    free(prime);
    return 0;
}