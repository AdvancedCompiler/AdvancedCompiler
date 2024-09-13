#include <stdio.h>
#define N 256 
int main() {
    int i;
    float A[N], B[N], C, D[N], E;
    C = 3.0;
    E = 4.0;
    for (i = 1; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }
    for (i = 1; i < N; i++)
        A[i + 1] = B[i] + C;//S1
    for (i = 1; i < N; i++)
        D[i] = A[i] + E;//S2
    printf("%f", D[3]);
}