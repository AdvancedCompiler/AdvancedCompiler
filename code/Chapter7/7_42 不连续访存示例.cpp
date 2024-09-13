#include <immintrin.h>
#include<stdio.h>
#define N 100
int main()
{
    float x11,x12;
    float x21,x22;
    float x[N];
    float y[N];
    for(int i=0;i<N;i+=1)
	    y[i]=i;
    for(int i=0;i<N;i+=4){
	__m128 vy=_mm_loadu_ps(y+i);
	__m128 vx=_mm_shuffle_ps(vy,vy,0);
	_mm_storeu_ps(&x[i],vx);
	}
    printf("X:\n");
    for(int i=0; i< N; i++)
    {
        printf("%f  ",x[i]);
    }
    printf("\n");
    return 0;
}


