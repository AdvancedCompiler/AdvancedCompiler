#include <stdio.h>
#include <immintrin.h>
#define N 48
float c[N];
int main()
{
    __m128 z = _mm_set_ps(3,2,1,0);
    __m128 z1 = _mm_set_ps(1,0,5,4);
    __m128 z2 = _mm_set_ps(5,4,3,2);

    for(int i=0; i< N; i+=12)
    {
        _mm_storeu_ps(&c[i],z);
        _mm_storeu_ps(&c[i+4],z1);
        _mm_storeu_ps(&c[i+8],z2);
    }
    for(int i=0;i< N;i++){
        printf("%f  ",c[i]);
        if((i+1)%6==0)
            printf("\n");
    }
    return 0;
}

