#include <stdio.h>
#include <immintrin.h>
#define N 8
//N is a multiple of 4
__m128 vecfun1(__m128 x,__m128 y){
	__m128 vz=_mm_mul_ps(x,y);
	return vz;
}
int main()
{
    float c[N],b[N],a[N];
    for(int i=0;i<N;i++){
	b[i]=i*2;
	c[i]=i/2;
}
    for(int i=0; i< N; i+=4)
    {
	__m128 vb=_mm_loadu_ps(&b[i]);
	__m128 vc=_mm_loadu_ps(&c[i]);
	__m128 va=vecfun1(vb,vc);
	_mm_storeu_ps(&a[i],va);
    }
    for(int i=0; i< N; i++)
    {
        printf("%f  ",a[i]);
    }
	printf("\n");
    return 0;
}
