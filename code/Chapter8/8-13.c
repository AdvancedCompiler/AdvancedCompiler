//false_share_test.c
#include <omp.h>
#define N 100000000
#define THRAED_NUM 8
int values[N];
int main(void)
{
    int sum[THRAED_NUM];
    #pragma omp parallel for
    for (int i = 0; i < THRAED_NUM; i++){
        for (int j = 0; j < N; j++){
            sum[i] += values[j] >> i;
        }
    }
    return 0;
}