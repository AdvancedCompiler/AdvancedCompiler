#include <stdio.h>
#define N 256 
int main() {
    int i;
    float A[N], B[N], C[N];
    for (i = 1; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 3.0;
    }
    for (i = 1; i < N; i++)
        A[i] = B[i] + 1;//S1
    for (i = 1; i < N; i++)
        C[i] = A[i] + C[i - 1];//S2
    printf("%f", C[3]);
}