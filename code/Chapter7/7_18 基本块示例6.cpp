#include <stdio.h>
#include <immintrin.h>
#define N 48
float c[N];
int main()
{
    __m128 z = _mm_set_ps(3,2,1,0);

    for(int i=0; i< N; i+=6)
    {
        _mm_storeu_ps(&c[i],z);
        c[i+4]=4;
        c[i+5]=5;
    }
    for(int i=0;i< N;i++){
        printf("%f  ",c[i]);
        if((i+1)%6==0)
            printf("\n");
    }
    return 0;
}

