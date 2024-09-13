//Compiler option added -mavx2
#include <stdio.h>
#include <x86intrin.h>
#define N 128
int main(){
	float b[N] = {0};
	float a[N] = {0};
	float sum ,s[N];
	sum = 0.0;
	int i,result;
	result = 0;
	__m128 gather = _mm_set_ps(0,0,0,0);
	__m128 ymm1,ymm2,ymm3,ymm4;
	for(i=0;i<N;i+=4){
		a[i] = i+2;
	}
	for(i=0;i<N;i++){                                                                                    
		printf("%0.2f ",a[i]);
	}
	printf("\n");
	for(i=0;i<N/4;i++){
		ymm1 = _mm_i32gather_ps(a+4*i,gather,sizeof(float));
		//set the first data in new ymm1
		_mm_storeu_ps(b+i,ymm1);
	}
	for(i=0;i<N;i++){
		printf("%0.2f ",b[i]);
	}
	printf("\n");
	for(i=0;i<N/4/4;i++){
		ymm1 = _mm_load_ps(b+4*i);
		ymm2 = _mm_set_ps(0,0,0,0);
		ymm3 = _mm_hadd_ps(ymm1,ymm2);
		ymm4 = _mm_hadd_ps(ymm3,ymm2);
		_mm_storeu_ps(s,ymm4);
		sum = s[0] + sum;
	}
	printf("sum = %f\n",sum);
}

