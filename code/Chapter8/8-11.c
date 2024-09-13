#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#define min(a,b) ((a)<(b)?(a):(b))
void matrixmulti(float N, float**x, float** y, float** z)
{
    int i, j, k,r;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            r = 0;
            for (k = 0; k < N; k++) {
                r = r + y[i][k] * z[k][j];
            }
            x[i][j] = r;
        }
    }
}
int main()
{
    int n, i, j;
    float ** x, ** y, ** z;
    n = 1024;
    double Total_time;
	clock_t start, end;
    printf("测试矩阵维数 n=%d\n",n);
    y = (float**)malloc(n * sizeof(float*));
    z = (float**)malloc(n * sizeof(float*));
    x = (float**)malloc(n * sizeof(float*));
    for (i = 0; i < n; i++)
    {
        y[i] = (float*)malloc(n * sizeof(float));
        z[i] = (float*)malloc(n * sizeof(float));
        x[i] = (float*)malloc(n * sizeof(float));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            y[i][j] = rand() % 10;
            z[i][j] = rand() % 10;
            x[i][j] = 0;
        }
    }
    start = clock();
    matrixmulti(n, x, y, z);
    end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("1024*1024的矩阵乘缓存分块优化前：%lf秒\n",Total_time);
    for(i=0;i<n;i++){
        free(y[i]);
        free(z[i]);
        free(x[i]);
    }
    free(y);
    free(z);
    free(x);
  return 0;
}