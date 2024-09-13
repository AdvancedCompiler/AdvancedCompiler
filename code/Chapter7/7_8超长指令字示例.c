#include <stdio.h>
#include <stdlib.h>
#define N 10

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
		for ( j = 0; j < N; j++)
		{
			c[i][j] = 0;
			for ( k = 0; k < N; k++)
				c[i][j] += a[i][k] * b[k][j];
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
 
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
