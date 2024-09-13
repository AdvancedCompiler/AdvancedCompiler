#include <stdio.h>
#define N 16
int main()
{
    float a[N],b[N],c[N];
    for(int i=0; i<N; i++)
    {   a[i]=1;
        b[i]=3+i;
        c[i]=1;
    }
    for(int i=0;i<N;i+=2){
        a[i]=2*b[i];
        a[i+1]=2*b[i+1];
        if(i<N/2){
            a[i]+=b[i];
            a[i+1]+=b[i+1];
        }else{
            a[i]-=b[i];
            a[i+1]-=b[i+1];
        }
        c[i]=a[i]+2;
        c[i+1]=a[i+1]+2;
    }
    for(int i=0; i<N; i++)
    {
        printf("a[%d]=%f  b[%d]=%f  c[%d]=%f  \n",i,a[i],i,b[i],i,c[i]);
    }
    return 0;
}

