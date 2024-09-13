#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_Threads 5
int arr[1000][5000];
int s1,s2;                                                                                                                                                                                                                
typedef struct{//创建结构体
  int first;
  int last;
  int result;
}MY_ARGS;
void *myfunc(void *args){
  int i,j;
  int s = 0;
  MY_ARGS *my_args = (MY_ARGS *)args;
  for(i=0;i<1000;i++)
    for(j = my_args->first;j < my_args->last;j++)
      s += arr[i][j];
  my_args -> result = s;
  return NULL;
}
int main(){
  int i,j;
  for(i=0;i<1000;i++)
    for(j=0;j<5000;j++){
     arr[i][j] = rand() % 50;
  pthread_t th1;
  pthread_t th2;
  pthread_t th3;
  pthread_t th4;
  pthread_t th5;
  MY_ARGS args1 = {0,1000,0};
  MY_ARGS args2 = {1000,2000,0};
  ...//此处需自行补充代码
  pthread_create(&th1,NULL,myfunc,&args1);
  pthread_create(&th2,NULL,myfunc,&args2);
  ...// 此处需自行补充代码
  pthread_join(th1,NULL);
  pthread_join(th2,NULL);
  ...//此处需自行补充代码
  printf("sum=%d\n",args1.result+args2.result +args3.result +args4.result + args5.result);
  return 0;
}
