#include <stdio.h> 
int A(int* i, int* j) {
    *i = 0;
    *j = 1;
    return *i;
}
void main() {
    int i, j;
    printf("%d", A(&i, &j));
}