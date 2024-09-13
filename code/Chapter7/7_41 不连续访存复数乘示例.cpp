#include <immintrin.h>
#include<stdio.h>
#define N 100
int main()
{
    float x11,x12;
    float x21,x22;
    float x[N];
    float y[N];
    int idx1=0,idx2=4,idx3=0;
    for(int i=0;i<N;i++)
	    y[i]=i;
    __m128 vx1,vx2,vx3,vx4,vy1,vy2,vy3,vy4,vxj1,vxj2,vxo1,vxo2,tp1,tp2,tp3,tp4;
    for(int i=0; i< N-idx2; i+=8)
    {
	vx1 = _mm_loadu_ps(y+i+idx1);
        vx2 = _mm_loadu_ps(y+i+idx1+4);
        vxj1 = _mm_shuffle_ps(vx1,vx2,_MM_SHUFFLE(2,0,2,0));
        vxo1 = _mm_shuffle_ps(vx1,vx2,_MM_SHUFFLE(3,1,3,1));
        vx3 = _mm_loadu_ps(y+i+idx2);
        vx4 = _mm_loadu_ps(y+i+idx2+4);
        vxj2 = _mm_shuffle_ps(vx3,vx4,_MM_SHUFFLE(2,0,2,0));
        vxo2 = _mm_shuffle_ps(vx3,vx4,_MM_SHUFFLE(3,1,3,1));
        vy1 = _mm_mul_ps(vxj1,vxj2);
        vy2 = _mm_mul_ps(vxo1,vxo2);
        vy3 = _mm_mul_ps(vxj1,vxo2);
        vy4 = _mm_mul_ps(vxj2,vxo1);
        tp1 = _mm_sub_ps(vy1,vy2);
        tp2 = _mm_add_ps(vy3,vy4);
        tp3 = _mm_shuffle_ps(tp1,tp2,_MM_SHUFFLE(1,0,1,0));
        tp4 = _mm_shuffle_ps(tp1,tp2,_MM_SHUFFLE(3,2,3,2));
        tp3 = _mm_shuffle_ps(tp3,tp3,_MM_SHUFFLE(3,1,2,0));
        tp4 = _mm_shuffle_ps(tp4,tp4,_MM_SHUFFLE(3,1,2,0));
        _mm_storeu_ps(x+i+idx3,tp3);
        _mm_storeu_ps(x+i+idx3+4,tp4);
    }
    printf("X:\n");
    for(int i=0; i< N; i++)
    {
        printf("%f  ",x[i]);
    }
    printf("\n");
    return 0;
}


