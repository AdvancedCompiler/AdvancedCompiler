#include <stdio.h>
#define N 256 
int main() {
    int i;
    float a[N], b[N], x[N], y[N];
    for (i = 0; i < N; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
    }
    for (i = 0; i < N; i++) {
        x[i] = a[i] + b[i];
        y[i] = a[i] - b[i];
    }
    printf("%f\n", x[4]);
    printf("%f\n", y[3]);
}