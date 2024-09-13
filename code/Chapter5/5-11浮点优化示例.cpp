#include <stdio.h>
#define N 128
int main( ){
     float sum = 0;
        float a[N];
           int i,j;
              for(i=0;i<N;i++){
                       a[i] = i;
                          }
                 for(j=0;j<N;j++) {
                          sum = sum + a[j];
                             }
                    printf("sum = %f",sum);
}

