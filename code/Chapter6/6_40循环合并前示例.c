#include <stdio.h>
#define N 256 
int main() {
    int i;
    float A[N], B[N], C, D[N], E;
    C = 1.0;
    E = 2.0;
    for (i = 1; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }
    for (i = 1; i < N; i++)
        A[i] = B[i] + C;//S1语句
    for (i = 1; i < N; i++)
        D[i] = A[i + 1] + E;//S2语句
}