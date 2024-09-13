#include <immintrin.h>
#include <stdio.h>
#define N 100
int main()
{
	float a[N],b[N],c[N],d[N];    
	for(int i=0; i< N; i++)
	{
		b[i]=2;
		c[i]=i;
		d[i]=-i;
	}
    for(int i=0; i< N; i+=4)
    {
        __m128 v1 = _mm_loadu_ps(&b[i]);
        __m128 v2 = _mm_loadu_ps(&c[i]);
        __m128 v3 = _mm_mul_ps(v1, v2);
        __m128 v4 = _mm_loadu_ps(&d[i]);
        __m128 v5 = _mm_add_ps(v4, v3);
        _mm_storeu_ps(&a[i],v5);
    }
    printf("a:\n");
    for (int i = 0; i <N; i++)
    {
        printf("%f  ", a[i]);
    }
    printf("\n");
    return 0;
}



