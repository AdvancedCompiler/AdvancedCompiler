#include <stdio.h>
#include <stdlib.h>
#define N 12
float a[N],b[N],c[N],w[N],v[N],m[N],n[N],p[N],x[N],y[N];
int main()
{
for(int i=0;i<N;i++){
	a[i]=i+1;
	b[i]=i*2;
	c[i]=i*10;
	w[i]=i+2;
	v[i]=i-1;
	m[i]=i+3;
	n[i]=i-2;
	p[i]=i;
	x[i]=i;
	y[i]=i;
}
    
for(int i=0; i<N; i++)
    {
	    v[i]=(a[i]>0&&a[i]>b[i])?w[i]:v[i];
	    p[i]=(a[i]>0&&a[i]>b[i]&&b[i]>10)?m[i]:p[i];
	    p[i]=(a[i]>0&&a[i]>b[i]&&b[i]<=10)?n[i]:p[i];
	    x[i]=(a[i]>0&&a[i]>b[i]&&b[i]<=10&&c[i]<100)?y[i]:x[i];
    }
    printf("v:\n");
    for(int i=0; i<N; i++)
    {
        printf("%f  ",v[i]);
    }
    printf("\n");
    printf("p:\n");
    for(int i=0; i<N; i++)
    {
        printf("%f  ",p[i]);
    }
    printf("\n");
    printf("x:\n");
    for(int i=0; i<N; i++)
    {
        printf("%f  ",x[i]);
    }
    printf("\n");
    return 0;
}

