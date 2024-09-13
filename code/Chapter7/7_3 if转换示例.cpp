
//7.3  if±ä»»1
#include<stdio.h>
#define N 100
void main()
{
    int a[N];
    int d[N];
    int c[N];
    int m[N];
    int n[N];
    for(int i = 0; i < N; i++)
    {
        a[i] = 0;
        m[i]=0;
        c[i]=i;
        d[i]=i+1;
        n[i]=i+2;
    }
    int C0=1;
    int C1=2;
    int D0=3;
    for(int i=0; i<N; i++)
    {
        if(i*2>2)
        {
            c[i]=C0;
        }
        else if(i*2<2)
        {
            c[i]=C1;
        }
        else
        {
            d[i]=D0;
        }
    }
    for(int i=0; i<N; i++)
    {
        printf("c[i]=%d d[i]=%d\n",c[i],d[i]);
    }
return 0;
}

