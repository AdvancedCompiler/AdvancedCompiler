#include <stdio.h>
void func1(int* x, int n) {
    for (int k = 1; k < n; k++)
        x[k] = x[k] + k;
}
int main() {
    int i;
    const int n = 256;
    int a[n];
    for (i = 0; i < n; i++)
        a[i] = i;
    func1(&a[0], i);
    printf("%d", a[5]);
}