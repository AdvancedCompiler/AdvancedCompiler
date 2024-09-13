#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#define min(a,b) ((a)<(b)?(a):(b))
void matrixmulti_1(int N, int** x, int** y, int** z,int S)
{//S为分块后小矩阵的长度
    int kk,jj,i, j, k, r;
    for (jj = 0; jj < N; jj = jj + S) {
        for (kk = 0; kk < N; kk = kk + S) {
            for (i = 0; i < N; i++) {
                for (j = jj; j < min(jj + S , N); j++) {
                    r = 0;
                    for (k = kk; k < min(kk + S , N); k++)
                        r = r + y[i][k] * z[k][j];
                    x[i][j] = x[i][j] + r;
                }
            }
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
    printf("\n");
    start = clock();
    matrixmulti_1(n, x, y, z,16);
    end = clock();
	Total_time=(double)(end - start) / CLOCKS_PER_SEC;
	printf("1024*1024的矩阵乘缓存分块优化后：%lf秒\n",Total_time);
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