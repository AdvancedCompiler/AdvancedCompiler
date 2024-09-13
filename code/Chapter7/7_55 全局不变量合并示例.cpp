#include <immintrin.h>
#include <stdio.h>
#define N 100
int main()
{
	float a[N];
	float b[N];
	float d[N];
	float x[N];
	float C=3;
	__m128 V1,V2,V3;
	for(int i=0; i<N; i++)
	{
		b[i]=i;
		x[i]=i+1;
	}
    V1 = _mm_set_ps(C, C, C, C);
    for(int i=0; i<N; i+=4)
    {
        V2 = _mm_load_ps(&b[i]);
        V3 = _mm_mul_ps(V1,V2);
        _mm_store_ps(&a[i], V3);
    }
    for(int i=0; i<N; i+=4)
    {
    	V1 = _mm_set_ps(C, C, C, C);
        V2 = _mm_load_ps(&x[i]);
        V3 = _mm_add_ps(V1,V2);
        _mm_store_ps(&d[i], V3);
    }
    printf("a:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%f  ", a[i]);
    }
    printf("\n");
    printf("d:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%f  ", d[i]);
    }
    printf("\n");
    return 0;
}
