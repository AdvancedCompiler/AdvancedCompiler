#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
int Ti = 3;
#define min(a,b) ((a)<(b)?(a):(b))
void func(float* A, float* B, int NI, int NJ) {
    for (int ii = 0; ii < NI; ii += Ti) {
        for (int j = 0; j < NJ; ++j) {
            for (int i = ii; i < min(ii + Ti, NI); ++i) {
                A[i] += B[j * NI + i]; // S
            }
        }
    }
}
int main(){
    int i;
    float* A, * B;
    int na=6, nb=12;
    A =  (float*)malloc(na * sizeof(float));;
    B =  (float*)malloc(100 * sizeof(float));;
    for ( i = 0; i < na; i++) {
        A[i] = rand() % 10;
    }
    for ( i = 0; i < 100; i++) {
        B[i] = rand() % 10;
    }
    printf("数组A的值为：\n");
    for (int i = 0; i < na; i++) {
        printf(" %.5lf ", A[i]);
    }
    printf("\n不展开运算后数组A的值为：\n");
    func(A, B, na, nb);
    for (int i = 0; i < na; i++) {
        printf(" %.5f ",A[i]);
    }
    free(A);
    free(B);
    return 0;
}