#include <stdio.h>
int main( ){
int i,N,sum;
N=1024;
int A[N],B[N];
#pragma clang loop vectorize(enable)
#pragma clang loop interleave(enable)
  for (i = 0; i < N; ++i) {
      sum= A[i] + B[i];                      
    }
          return sum;
}

