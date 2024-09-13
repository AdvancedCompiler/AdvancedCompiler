#include <stdio.h>
#include <stdlib.h>
int main( ){
  int i,N,sum;
  N=1024;
  sum = 0;
  int A[N],B[N];
  for (i = 0; i < N; ++i) {
    A[i] = i;
    B[i] = rand()%10;
  }
#pragma clang loop vectorize_width(4) interleave_count(8)
  for (i = 0; i < N; ++i) {
    sum= sum + A[i] + B[i];                      
  }
  printf("%d\n",sum);
#pragma clang optimize off
}

