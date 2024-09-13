#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
int Ti = 3;
#define min(a,b) ((a)<(b)?(a):(b))
void func_unroll4(float* A, float* B, int NI, int NJ) {
    for (int ii = 0; ii < NI; ii += Ti) {
        for (int j = 0; j < NJ; j += 4) {//第二层循环展开四次
            for (int i = ii; i < min(ii + Ti, NI); ++i) {//连加四次以后再将数据存储到A[i]
                A[i] += B[j * NI + i];
                A[i] += B[(j + 1) * NI + i];
                A[i] += B[(j + 2) * NI + i];
                A[i] += B[(j + 3) * NI + i];
            }
        }
    }
}
int main(){
    float* A, * B;
    int i,na=6, nb=12;
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
    printf("\n循环展开四次运算后数组A的值为：\n");
    func_unroll4(A, B, 6, 12);
    for ( i = 0; i < na; i++) {
        printf(" %.5f ", A[i]);
    }
    free(A);
    free(B);
    return 0;
}