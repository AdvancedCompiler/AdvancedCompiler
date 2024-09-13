#include <stdio.h>
#define N 1280
int main(){
        int sum = 0;
	int a[N],b[N];
	int i,j;
        for(i=0;i<N;i++)
        {
        	a[i] = i;
		b[i] = i + 3;
	}

        for(j=0;j<N;j++)
        {
        	sum = sum + a[j+2] + b[j+2];
	}
        printf("sum = %d",sum);
}
