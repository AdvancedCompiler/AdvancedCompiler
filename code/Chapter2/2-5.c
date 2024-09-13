#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define n 1024 
int x[n][n],y[n][n],z[n][n];
int a,b,i,j,k,r;
void matrixmulti(int N,  int x[n][n], int y[n][n], int z[n][n]){
for (k = 0; k < N; k++) {//循环交换
        for (i = 0; i < N; i++) {
            r = y[i][k];
            for (j = 0; j < N; j++) {
                x[i][j] += r* z[k][j];
            }
        }
}
int main(){
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            y[i][j] = rand() % 10;
            z[i][j] = rand() % 10;
            x[i][j] = 0;
        }
    }
struct timeval starttime,endtime;
   gettimeofday(&starttime,0);
   matrixmulti(n, x, y, z);
gettimeofday(&endtime,0);
   doubletimeuse=(endtime.tv_sec-starttime.tv_sec)+(endtime.tv_usec-starttime.tv_usec)/1000000.0;
   printf("run time = %f s\n", timeuse);
return 0;
}