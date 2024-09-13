#include<stdio.h>
#include<stdlib.h>
int  N = 101;
int x[] = { 8, -33, 16, 9, -12, 45, 67 };
int MaxSubsequenceSum(){
    int maxsofar = -0x3f3f3f3f;
    int f[100];
    f[0] = 0;
    for (int i = 1; i < 8; i++) {
        f[i] = max(f[i - 1] + x[i], x[i]);
        maxsofar = max(f[i], maxsofar);
    }
    return  maxsofar;
}
int main(){
    printf("%d", MaxSubsequenceSum());
    return 0;
}