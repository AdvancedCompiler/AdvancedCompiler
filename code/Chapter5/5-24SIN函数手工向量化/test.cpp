#include <time.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#define pi 3.1415926
using namespace std;
int main(){
  clock_t start, end;
  double time1 = 0;
  start = clock();
  for(int j=1;j<=100000000;j++){
    sin(pi/2);
  }
  end = clock();
  time1 = end -start;
  cout << "系统库中sin函数计算sin(pi/2)用时  " << (double)time1 / CLOCKS_PER_SEC << "s" <<endl;
  cout << "sin(pi/2)= " << sin(pi/2)<< endl <<endl;
  return 0;
}                     
