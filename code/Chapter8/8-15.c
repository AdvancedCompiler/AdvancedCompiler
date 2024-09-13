#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define nop
#define N 700
int main(int argc, const char *argv[])
{
    unsigned long i, j, k;
 
    int res[N][N], mul1[N][N], mul2[N][N];
    clock_t start, end;
    double time1 = 0;
    double time2 = 0;
    for (i = 0; i < N; ++i) {
          for (j = 0; j < N; ++j) {
                   mul1[i][j] = (i + 1) * j;
                   mul2[i][j] = i * j;
             }
      }
     start = clock();
    nop;nop;nop;
    for (i = 0; i < N; ++i)
          for (j = 0; j < N; ++j)                                                                                                                                                       
                   for (k = 0; k < N; ++k)
                          res[i][j] += mul1[i][k] * mul2[k][j];
    nop;nop;nop;
    end = clock();
    time1 = end - start;
    printf("Run Time1 %f s\n", (double)time1 / CLOCKS_PER_SEC);
    __builtin_prefetch(mul1, 0, 3);
    __builtin_prefetch(mul2, 0, 0);
    __builtin_prefetch(res,  1, 3);
    start = clock();
    nop;nop;nop;
    for (i = 0; i < N; ++i)
          for (j = 0; j < N; ++j)
                  for (k = 0; k < N; ++k)
                          res[i][j] += mul1[i][k] * mul2[k][j];
    nop;nop;nop;
    end = clock();
    time2 = end - start;        
printf("Run Time2 %f s\n", (double)time2 / CLOCKS_PER_SEC);
    printf("Time2 and Time1 upgrade %f% \n", (double)(time1 - time2) / time1 * 100);
    return 0;
} 