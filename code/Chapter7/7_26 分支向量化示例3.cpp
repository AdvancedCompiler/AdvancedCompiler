#include <stdio.h>
#include <emmintrin.h>
#include <stdlib.h>
#define N 12
float a[N],b[N],c[N],w[N],v[N],m[N],n[N],p[N],x[N],y[N];
int main()
{
for(int i=0;i<N;i++){
	a[i]=i+1;
	b[i]=i*2;
	c[i]=i*10;
	w[i]=i+2;
	v[i]=i-1;
	m[i]=i+3;
	n[i]=i-2;
	p[i]=i;
	x[i]=i;
	y[i]=i;
}
    
for(int i=0; i<N; i+=4)
    {
	__m128 va=_mm_loadu_ps(&a[i]);
	__m128 vb=_mm_loadu_ps(&b[i]);
	__m128 vw=_mm_loadu_ps(&w[i]);
	__m128 vv=_mm_loadu_ps(&v[i]);
	__m128 v0=_mm_set_ps(0,0,0,0);
	__m128 com1=_mm_cmpgt_ps(va,v0);
	__m128 com2=_mm_cmpgt_ps(va,vb);
	com1=_mm_and_ps(com1,com2);
	vw=_mm_and_ps(vw,com1);
	vv=_mm_andnot_ps(com1,vv);
	vv=_mm_add_ps(vw,vv);
	_mm_storeu_ps(&v[i],vv);
    }
    printf("v:\n");
    for(int i=0; i<N; i++)
    {
        printf("%f  ",v[i]);
    }
    printf("\n");
 /*   printf("p:\n");
    for(int i=0; i<N; i++)
    {
        printf("%d  ",p[i]);
    }
    printf("\n");
    printf("x:\n");
    for(int i=0; i<N; i++)
    {
        printf("%d  ",x[i]);
    }
    printf("\n");*/
    return 0;
}

