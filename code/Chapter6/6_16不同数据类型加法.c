#include <immintrin.h>
#include<stdio.h>
#include <time.h>
#include<malloc.h>
#include <stdlib.h>
static void add_float(const float* in1, const float* in2, volatile float* out1, const size_t n) {
    for (size_t i = 0; i < n; i += 4) {
        __m128 a = _mm_loadu_ps(&in1[i]);
        __m128 b = _mm_loadu_ps(&in2[i]);
        __m128 result = _mm_add_ps(a, b);
        _mm_store_ps((float*)&out1[i], result);
    }
}
static void add_int(const int* in3, const int* in4, volatile int* out2, const size_t n) {
    __m128i x, y, z;
    for (size_t i = 0; i < n; i += 4) {
        x = _mm_loadu_si128((__m128i*)in3);
        y = _mm_loadu_si128((__m128i*)in4);
        z = _mm_add_epi32(x, y);
        _mm_store_si128((__m128i*)out2, z);
    }
}
int main()
{
    int n = 128, i;
    clock_t start, end;
    float* in1 = (float*)malloc(n * sizeof(float));
    float* in2 = (float*)malloc(n * sizeof(float));
    volatile float* out1 = (float*)malloc(n * sizeof(float));//用于float运算
    int* in3 = (int*)malloc(n * sizeof(int));
    int* in4 = (int*)malloc(n * sizeof(int));
    volatile int* out2 = (int*)malloc(n * sizeof(int));//进行int数据运算
    for (i = 0; i < n; i++)
    {
        in1[i] = rand() % 10;
        in2[i] = rand() % 10;
        in3[i] = rand() % 10;
        in4[i] = rand() % 10;
    }
    //SSE优化的float矩阵乘
    start = clock();
    add_float(in1, in2, out1, n);
    end = clock();
    printf("t_float：%d\nus", double(end - start));
    double time1 = double(end - start);
    start = clock();
    add_int(in3, in4, out2, n);
    end = clock();
    printf("t_int：%lf\nus", double(end - start));
    printf("speed-up =%lf\n倍", time1 / double(end - start));
    free(in1);
    free(in2);
    free(in3);
    free(in4);
}