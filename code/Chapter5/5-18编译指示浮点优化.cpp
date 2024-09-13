#include <stdio.h>
int main( ){
  int i,a;
  int N = 1024;
  int b[N],c[N],d[N];
  for(i=0;i<N;i++) {
    b[i] = i;
    c[i] = i+1;
  }
  for(i=0;i<N;i++) {
    #pragma clang fp contract(fast)
    a = b[i] * c[i];
    d[i] += a;
  }
  printf("%d",d[3]);
}

