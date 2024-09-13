#include <stdio.h>
#define N 128
int main(){
        int sum = 0;
	int sum1 = 0;
	int a[N],b[N];
	int i,j;
        for(i=0;i<N;i++){
        	a[i] = i;
		b[i] = i+1;
	}
        for(i=0;i<N;i++){
        	sum = sum + a[i];
	}
	
	for(i=0;i<N;i++){
        	b[i+1] = b[i] + b[i+2];
	}
        printf("sum = %d",sum);
}
