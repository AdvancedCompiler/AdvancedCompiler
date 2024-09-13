#include<stdio.h>

#define N 100
int main(int argc, char* argv[])
{
    float a[N];
    float b[N];
    float c[N]={};
    for(int i=0; i< N; i++)
    {
        a[i]=i+2;
        b[i]=i*3;
    }
    for(int i=0; i< N; i++)
    {
       a[i]=b[i];
    }
    for (int i = 0; i < N; i++)
    {
        printf("a[i]=%f b[i]=%f\n\n", a[i],b[i]);
    }
    return 0;
}
