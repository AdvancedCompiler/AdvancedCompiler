#include<stdio.h>
#include<malloc.h>
float x=5.5642;//一个随机的float值
void function(float* a, int N)
{
    int i;
    float phi = 2.541, delta, alpha,temp;
    temp = x;
    delta = temp * temp;
    alpha = temp / 2;
    for (i = 0; i < N; i++)
        a[i] = temp * phi;
}
int main()
{
    float*b;
    int n=100;
    b = (float*)malloc(n * sizeof(float));
    function(b, n);
    free(b);
    return 0;
}