#include <stdio.h>
#include <stdlib.h>
#define N 4

float a[N][N],v[N][N];

int main(){

	int i,j;
	float sum0=0;
	float sum1=0;
	float sum2=0;
	int vlast=rand()%10;
		printf("%d\n",vlast);
		printf("A:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a[i][j]=i+j;
			printf("%f  ",a[i][j]);
		}
		printf("\n");
	}
	
		printf("V:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			v[i][j]=i-j;
			printf("%f  ",v[i][j]);
		}
		printf("\n");
	}
	i=0;
	while (i< vlast) {
		sum0 += a[0][0]*v[0][i] + a[0][1]*v[0][i] + a[0][2]*v[0][i];
		sum1 += a[1][0]*v[1][i] + a[1][1]*v[1][i] + a[1][2]*v[1][i];
		sum2 += a[2][0]*v[2][i] + a[2][1]*v[2][i] + a[2][2]*v[2][i];
		i++;
	}

	
	printf("sum0=%f,sum1=%f,sum2=%f \n",sum0,sum1,sum2);
return 0;
} 

