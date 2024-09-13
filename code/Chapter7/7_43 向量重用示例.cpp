#include <immintrin.h>
#include <stdio.h>

#define N 100
int main()
{
    float a[N+2];
    float c[N];
    for(int i=0; i< N+2; i++)
    {
        a[i]=i;
    }
    	__m128 va1 = _mm_load_ps(a);
    for(int i=0; i< N; i+=4)
    {
        __m128 va2 = _mm_load_ps(&a[i+4]);
        __m128 V1 = _mm_shuffle_ps(va1,va2,_MM_SHUFFLE(1,0,3,2));
        _mm_store_ps(&c[i],V1);
        va1=va2;
    }
    printf("c:\n");
    for(int i=0; i< N; i++)
    {
        printf("%f  ",c[i]);
    }
    printf("\n");
    return 0;
}


