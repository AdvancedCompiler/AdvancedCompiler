#include <stdio.h>
#define N 9

float fun1(float x,float y){
	float z=x*y;
	return z;
}
int main()
{
    float c[N],b[N],a[N];
    for(int i=0;i<N;i++){
	b[i]=i*2;
	c[i]=i/2;
}
    for(int i=0; i< N; i++)
    {
       a[i] = fun1(b[i],c[i]);

    }
    for(int i=0; i< N; i++)
    {
        printf("%f  ",a[i]);
    }
	printf("\n");
    return 0;
}
