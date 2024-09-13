#include <immintrin.h>
#include <stdio.h>
#define N 100
int main()
{
	float a[N],b[N],c[N],d[N];
    for (int i = 0; i < N; i++)
    {
        b[i] = i*2;
        c[i] = i;
    }

    for (int i = 0; i < N; i += 4)
    {
        __m128 vb = _mm_loadu_ps(b + i);
        __m128 vc = _mm_loadu_ps(c + i);
        __m128 va = _mm_add_ps(vb, vc);
        _mm_storeu_ps(a + i, va);
        __m128 vd = _mm_sub_ps(vb,vc);
        _mm_storeu_ps(d + i, vd);
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



