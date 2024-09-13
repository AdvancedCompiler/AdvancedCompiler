#include <stdio.h>
#define N 100
int main()
{
    float x11,x12;
    float x21,x22;
    float x[N];
    float y[N];
    int idx1=0,idx2=4,idx3=0;
    for(int i=0;i<N;i++)
	    y[i]=i;
    for(int i=0; i<N-4; i+=2)
    {
	    x11 = y[idx1+i];
	    x12 = y[idx1+i+1];
	    x21 = y[idx2+i];
	    x22 = y[idx2+i+1];
	    x[idx3+i] = x11*x21-x12*x22;
            x[idx3+i+1] = x12*x21+x11*x22;
    }
    printf("X:\n");
    for(int i=0; i<N; i++)
    {
        printf("%f  ",x[i]);
    }
    printf("\n");
    return 0;
}
