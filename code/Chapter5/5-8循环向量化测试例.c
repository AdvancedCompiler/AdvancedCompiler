#include <stdio.h>
#define N 1280
int main(){
  int sum = 0;
  int a[N];
  int i,j;
  for(i=0;i<N;i++){
    a[i] = i;
  }
  for(j=0;j<N;j++){
    sum = sum + a[j];
  }
  printf("sum = %d",sum);
}

