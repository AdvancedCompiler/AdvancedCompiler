#include <stdio.h>
#include <immintrin.h>
#define N 48
float c[N];
int main()
{

    for(int i=0; i< N; i+=24)
    {
        c[i]=0;c[i+6]=0;c[i+12]=0;c[i+18]=0;
        c[i+1]=1;c[i+1+6]=1;c[i+1+12]=1;c[i+1+18]=1;
        c[i+2]=2;c[i+2+6]=2;c[i+2+12]=2;c[i+2+18]=2;
        c[i+3]=3;c[i+3+6]=3;c[i+3+12]=3;c[i+3+18]=3;
        c[i+4]=4;c[i+4+6]=4;c[i+4+12]=4;c[i+4+18]=4;
        c[i+5]=5;c[i+5+6]=5;c[i+5+12]=5;c[i+5+18]=5;
    }
    for(int i=0;i< N;i++){
        printf("%f  ",c[i]);
        if((i+1)%6==0)
            printf("\n");
    }
    return 0;
}

