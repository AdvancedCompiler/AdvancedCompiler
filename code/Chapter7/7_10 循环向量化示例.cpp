//代码7.7 循环的向量化2
#include <xmmintrin.h>
#include <stdio.h>
#define N 100

int main(int argc, char* argv[])
{
    float a[N];
    float b[N];
    for(int i=0; i< N; i++)
    {
             b[i]=i*3;
    }
    for(int i=0; i<(N/4); i++)
    {
        __m128 second = _mm_load_ps (b+i*4);
        _mm_store_ps (a+i*4, second);
    }
    for (int i = 0; i < N; i++)
    {
        printf("a[%d]=%f b[%d]=%f\n\n",i, a[i],i,b[i]);
    }
return 0;
}
