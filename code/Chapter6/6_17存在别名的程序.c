#include <stdio.h>                                                                                                                                                                                                
#define N 1024
void add(int* a, int* b) {
    int C = 5;
    for (int i = 0; i < N; i++)
        a[i] = b[i - 1] + C;
}
int main() {
    int a[N], b[N];
    int i;
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i + 1;
    }
    add(a, b);
    printf("%d\n", a[1]);
}