#include <stdio.h>
#define N 100

int main(){
	float a[N],b[N];
	float C=3;
	for(int i=0;i<N;i++)
		b[i]=i;

	for(int i=0;i<N;i++)
		a[i]=C*b[i];
	printf("a:\n");	
	for(int i=0;i<N;i++)
		printf("%f  ",a[i]);
	printf("\n");	
	return 0;
}
