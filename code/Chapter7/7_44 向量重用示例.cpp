#include <immintrin.h>
#include <stdio.h>
#define N 100
int main()
{
    float a[N];
    float b[N];
    float c[N];
    float d[N];
    for(int i=0; i< N; i++)
    {
        b[i]=i*2;
	c[i]=i;
    }
    for(int i=0; i< N; i++)
    {
	a[i]=b[i]+c[i];
	d[i]=b[i]-c[i];
    }
    printf("a:\n");
    for(int i=0; i< N; i++)
    {
        printf("%f  ",a[i]);
    }
    printf("\n");
    printf("d:\n");
    for(int i=0; i< N; i++)
    {
        printf("%f  ",d[i]);
    }
    printf("\n");
    return 0;
}


