#include <stdio.h>
#include <stdlib.h>
#define N 1280
int main(){
	int A[N],B[N],C[N],D[N],E[N];
	int i,j,sum;
        for(i=0;i<N;i++){
			B[i] = rand();
			C[i] = rand();
		}
	

        for(i=1;i<N;i++){
  		A[i] = i;
  		B[i] = 2 + B[i];
  		C[i] = 3 + C[i - 1];
	}

	for(i=0;i<N;i++){
			printf("%d",B[i]);
			printf("%d",A[i]);
			printf("%d",C[i]);
	}
	//printf("%d",sum);
}
