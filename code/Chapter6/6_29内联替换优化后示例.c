#include <stdio.h>
void func1(int* x, int k) {
    x[k] = x[k] + k;
}
int main() {
    int i;
    const int n = 256;
    int a[n];
    for (i = 0; i < n; i++)
        a[i] = a[i] + i;
}