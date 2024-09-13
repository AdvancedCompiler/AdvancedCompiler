//代码  循环展开
#include <stdio.h>
#define N 48
int main()
{
    float c[N]={};
    
    for ( int i = 0; i < N; i+=6)
    {
        c[i+0] = 0;
        c[i+1] = 1;
        c[i+2] = 2;
        c[i+3] = 3;
        c[i+4] = 4;
        c[i+5] = 5;

    }
    printf("结果为\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d  ",c[i]);

        if((i+1)%6==0)
        {
            printf("\n");
        }

    }
    return 0;
}
