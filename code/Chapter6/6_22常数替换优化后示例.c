#include <stdio.h>
int main() {
    float a = 16;
    int i;
    const int n = 256;
    float x[n];
    for (i = 0; i < n; i++) {
        x[i] = 4.0 + i;
    }
    return 0;
}