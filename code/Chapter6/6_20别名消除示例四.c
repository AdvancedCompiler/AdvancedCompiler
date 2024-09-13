#include <stdio.h>                                                                                                                                                                  
int A(int* restrict i, int* restrict j) {
    *i = 0;
    *j = 1;
    return 0;
}
void main() {
    int i, j;
    printf("%d", A(&i, &j));
}