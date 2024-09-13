#include <stdio.h>
#define N 128
int main(){
  float a[N] = {0};
  float sum;
  int i;
  sum = 0;
  for(i=0;i<N;i+=4){
    a[i] = i+2;
  }
  for(i=0;i<N;i++){
    printf("%.2f ",a[i]);
  }
  printf("\n");
  for(i=0;i<N;i++){
    sum = a[i] + sum;
  }
  printf("sum = %.2f\n",sum);                                                                          
}

