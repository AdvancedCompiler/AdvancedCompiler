#include <stdio.h>                                                                              
#include <x86intrin.h>
#define N 128
float sum = 0;
int main(){
  float a[N];
  float s[4] = {0,0,0,0};
  int i,j;
  __m128 ymm0,ymm1,ymm2,ymm3;
  for(i=0;i<N;i++){
    a[i] = i+1;
  }
  for(i=0;i<N/4;i++){
    ymm0 = _mm_load_ps(a+4*i);
    ymm1 = _mm_set_ps(0,0,0,0);
    ymm2 = _mm_hadd_ps(ymm0,ymm1);
    ymm3 = _mm_hadd_ps(ymm2,ymm1);
    _mm_storeu_ps(s,ymm3);
    sum = s[0] + sum;
  }
  printf("sum = %f",sum);
}

