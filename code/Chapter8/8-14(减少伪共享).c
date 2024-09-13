#include <omp.h>
#define N 100000000
#define THRAED_NUM 8
int values[N]；
int main(void)
{
    int sum[THRAED_NUM]；
    #pragma omp parallel for
    for (int i = 0； i < THRAED_NUM； i++){   
        int local_sum；
        for (int j = 0； j < N； j++){
            local_sum += values[j] >> i；
        }
        sum[i] = local_sum；
    }
    return 0；
}