/*for book5-4 vec sin  */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <x86intrin.h>
#define pi 3.1415926
using namespace std;

double Sin(double x1,double x2,double x3,double x4){
  double result =0.0;
  result = sin(x1);
  result = sin(x2);
  result = sin(x3);
  result = sin(x4);
  return result;
}

int main(){
  clock_t start, end;
  double result1;
  double time1 = 0;
  start = clock();
  __m256 ymm;
  for(int j=1;j<=100000000;j+=4){
    result1 = Sin(pi/2,pi/2,pi/2,pi/2);
  }
  end = clock();
  time1 = end - start;
  printf("自定义Sin函数计算sin(pi/2)=%f 用时 %f s \n",result1,(double)time1 / CLOCKS_PER_SEC);
 

  start = clock();
  for(int j=1;j<=100000000;j++){
    result1 = sin(pi/2);
  }
  end = clock();
  time1 = end -start;
  printf("原始Sin函数计算sin(pi/2)=%f 用时 %f s \n",result1,(double)time1 / CLOCKS_PER_SEC);

  return 0;
}
