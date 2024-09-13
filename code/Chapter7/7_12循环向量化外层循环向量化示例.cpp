#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#define N 4
//NÎª4µÄ±¶Êý
float a[N][N],b[N][N],c[N][N];

int main(){

	int i,j,k;
		printf("A:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a[i][j]=i+j;
			printf("%f  ",a[i][j]);
		}
		printf("\n");
	}
	
		printf("B:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			b[i][j]=i-j;
			printf("%f  ",b[i][j]);
		}
		printf("\n");
	}
	
	for (i = 0; i < N; i++)
	{
		for ( j = 0; j < N; j+=4)
		{
			__m128 sum=_mm_set_ps(0,0,0,0);
			for ( k = 0; k < N; k++){
			__m128 vb=_mm_load_ps(&b[k][j]);
			__m128 va=_mm_set_ps(a[i][k],a[i][k],a[i][k],a[i][k]);
			__m128	vab=_mm_mul_ps(va,vb);
			sum=_mm_add_ps(vab,sum);
			}
		_mm_store_ps(&c[i][j],sum);
		}
	}
	printf("C:\n");

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f  ",c[i][j]);
		}
		printf("\n");
	}
return 0;

} 

