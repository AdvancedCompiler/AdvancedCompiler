#include <stdio.h>
#define N 1335
float A[N][N+1];
int main(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N+1;j++)
			A[i][j]=i+j;
	for(int i=0;i<N;i++)
		for(int j=0;j<N+1;j++)
			A[i][j]=A[i][j]*2;
	for(int i=0;i<N;i++){
		for(int j=0;j<N+1;j++)
			printf("%f ",A[i][j]);
		printf("\n");
	}

	return 0;
}
