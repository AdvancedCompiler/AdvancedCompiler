#include <stdio.h>
#define N 100

int main(){
	float a[N],b[N];
	float d[N],x[N];
	float C=3;
	for(int i=0;i<N;i++){
		b[i]=i;
		x[i]=i+1;
	}
	for(int i=0;i<N;i++)
		a[i]=C*b[i];
	for(int i=0;i<N;i++)
		d[i]=C+x[i];
	printf("a:\n");	
	for(int i=0;i<N;i++)
		printf("%f  ",a[i]);
	printf("\n");	
	printf("d:\n");	
	for(int i=0;i<N;i++)
		printf("%f  ",d[i]);
	printf("\n");	
	return 0;
}
