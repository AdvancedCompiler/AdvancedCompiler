#include <stdio.h>
#define N 100
float A[N],B[N];
int main(){
	float C=0.5;
	for(int i=0;i<100;i++)
		A[i]=i*2;
	B[0]=0;
	for(int i=0;i<100;i++)
		B[i+1]=A[i+1]+C;
	for(int i=0;i<100;i++){
		printf("%f ",B[i]);
		if(i%10==0)
			printf("\n");
	}

	return 0;
}
