//´úÂë7.4 if±ä»»2
#include<stdio.h>
#define N 100

int main()
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
    for(int i=0; i< N; i++)
    {
        c[i]=(i*2>2)?C0:c[i];
        c[i]=((!(i*2>2))&&(i*2<2))?C1:c[i];
        d[i]=((!(i*2>2))&&(!(i*2<2)))?D0:d[i];
    }
    for(int i=0; i< N; i++)
    {
        printf("c[i]=%d d[i]=%d\n",c[i],d[i]);
    }
return 0;
}




