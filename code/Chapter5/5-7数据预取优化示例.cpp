#include <stdio.h>
int main( ){
  int arr[10];
  int i;
  for(i=0;i<10;i++){
      __builtin_prefetch(arr+i,1,3);
  }
  for(i=0;i<10000;i++){
      arr[i%10] = i;
  }
  for(i=0;i<10;i++){
      printf(“%d\n”,arr[i]);
  }
}

