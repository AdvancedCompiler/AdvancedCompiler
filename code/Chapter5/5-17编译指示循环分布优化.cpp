#include <stdio.h>
int main( ){
    int i,N;
    N=1024;
    int A[N],B[N],C[N],D[N],E[N];
    for (i = 0; i < N; ++i) {
        A[i] = i;
        B[i] = i + 1;
        D[i] = i + 2;
        E[i] = i + 3;
    }
    #pragma clang loop distribute(enable)
    for (i = 0; i < N; ++i) {
        A[i + 1] = A[i] + B[i];                        
        C[i] = D[i] * E[i];                            
    }
    printf("%d",A[8]);
}

