#include <immintrin.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
void swap(float* a, float* b) {
    float* temp = a;
    a = b;
    b = temp;
}
void sse_mul(int n, float** a, float** b, float** c)//float型的sse矩阵乘
{
    __m128 t1, t2, sum;
    //turning matrix into T(b)
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) swap(&b[i][j], &b[j][i]);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            c[i][j] = 0.0;
            sum = _mm_setzero_ps();
            for (int k = n - 4; k >= 0; k -= 4)
            {
                t1 = _mm_loadu_ps(a[i] + k);
                t2 = _mm_loadu_ps(b[j] + k);
                t1 = _mm_mul_ps(t1, t2);
                sum = _mm_add_ps(sum, t1);
            }
            sum = _mm_hadd_ps(sum, sum);
            sum = _mm_hadd_ps(sum, sum);
            _mm_store_ss(c[i] + j, sum);
            for (int k = (n % 4) - 1; k >= 0; --k)
            {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) swap(&b[i][j], &b[j][i]);
}
void swap_1(double* a, double* b) {
    double* temp = a;
    a = b;
    b = temp;
}
void sse_mul_1(int n, double** a, double** b, double** c)//double型的sse矩阵乘
{
    __m128d t1, t2, sum;
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) swap_1(&b[i][j], &b[j][i]);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            c[i][j] = 0.0;
            sum = _mm_setzero_pd();
            for (int k = n - 2; k >= 0; k -= 2)
            {
                t1 = _mm_loadu_pd(a[i] + k);
                t2 = _mm_loadu_pd(b[j] + k);
                t1 = _mm_mul_pd(t1, t2);
                sum = _mm_add_pd(sum, t1);
            }
            sum = _mm_hadd_pd(sum, sum);
            sum = _mm_hadd_pd(sum, sum);
            _mm_store_sd(c[i] + j, sum);
            for (int k = (n % 4) - 1; k >= 0; --k)
            {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) swap_1(&b[i][j], &b[j][i]);
}
int main()
{
    int n = 256, i, j;
    float** a, ** b, ** c;
    clock_t start, end;
    double Total_time;
    printf("测试矩阵维数n=%d", n);
    a = (float**)malloc(n * sizeof(float*));
    b = (float**)malloc(n * sizeof(float*));
    c = (float**)malloc(n * sizeof(float*));
    for (i = 0; i < n; i++)
    {
        a[i] = (float*)malloc(n * sizeof(float));
        b[i] = (float*)malloc(n * sizeof(float));
        c[i] = (float*)malloc(n * sizeof(float));
    }
    double** a1, ** b1, ** c1;
    a1 = (double**)malloc(n * sizeof(double*));
    b1 = (double**)malloc(n * sizeof(double*));
    c1 = (double**)malloc(n * sizeof(double*));
    for (i = 0; i < n; i++)
    {
        a1[i] = (double*)malloc(n * sizeof(double));
        b1[i] = (double*)malloc(n * sizeof(double));
        c1[i] = (double*)malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
            c[i][j] = 0;
            a1[i][j] = rand() % 10;
            b1[i][j] = rand() % 10;
            c1[i][j] = 0;
        }
    }
    //SSE优化的float矩阵乘
    start = clock();
    sse_mul(n, a, b, c);
    end = clock();
    Total_time=(double)(end - start) / CLOCKS_PER_SEC;
    printf("\nSSE float类型矩阵乘枆时：%lf秒",Total_time);
    double time1 = (double)(end - start);
    start = clock();
    sse_mul_1(n, a1, b1, c1);
    end = clock();
    Total_time=(double)(end - start) / CLOCKS_PER_SEC;
    printf("\nSSE double类型矩阵乘枆时：%lf秒",Total_time);
    printf("\nspeed-up =%lf倍", (double)(end - start) / time1);
    for (i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
        free(a1[i]);
        free(b1[i]);
        free(c1[i]);
    }
    free(a);
    free(b);
    free(c);
    free(a1);
    free(b1);
    free(c1);
return 0;
}