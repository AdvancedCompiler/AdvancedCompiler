#include <stdio.h>
#include <immintrin.h>
#define N 16
int main()
{
    float a[N],b[N],c[N];
    for(int i=0; i<N; i++)
    {   a[i]=1;
        b[i]=3+i;
        c[i]=1;
    }
//N is divisible by 8 in order to be correct
    for(int i=0;i<N;i+=4){
        __m128 va=_mm_loadu_ps(&a[i]);
        __m128 vb=_mm_loadu_ps(&b[i]);
	__m128 v2=_mm_set_ps(2,2,2,2);
	va=_mm_mul_ps(vb,v2);	
	_mm_storeu_ps(&a[i],va); 
        if(i<N/2){
       	    va=_mm_loadu_ps(&a[i]);
       	    vb=_mm_loadu_ps(&b[i]);
            va=_mm_add_ps(va,vb);
	    _mm_storeu_ps(&a[i],va); 
        }else{
       	    va=_mm_loadu_ps(&a[i]);
       	    vb=_mm_loadu_ps(&b[i]);
            va=_mm_sub_ps(va,vb);
	    _mm_storeu_ps(&a[i],va); 
        }
       	va=_mm_loadu_ps(&a[i]);
	__m128 vc=_mm_add_ps(va,v2);
	_mm_storeu_ps(&c[i],vc); 
}
    for(int i=0; i<N; i++)
    {
        printf("a[%d]=%f  b[%d]=%f  c[%d]=%f  \n",i,a[i],i,b[i],i,c[i]);
    }
    return 0;
}

