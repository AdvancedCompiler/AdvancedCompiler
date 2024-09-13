#include <stdio.h>
#define N 256
int main() {
    int i, temp, phi;
    int a[N], b[N], c[N], d[N], coff[N], diff[N];
    temp = 2;
    phi = 2;
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i + 1;
        c[i] = i + 2;
        d[i] = i + 3;
    }
    for (i = 0; i < N; i++) {
        temp = a[i] - b[i];
        coff[i] = (a[i] + b[i]) * temp;
    }
    for (i = 0; i < N; i++) {
        diff[i] = (c[i] + d[i]) / phi;
    }
}