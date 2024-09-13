#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 10000000;
int a[N],b[N],c[N];
int i;
int main(){
        for(i= 0; i <N; i++){
                a[i]=i+ 1;
                b[i]=i+2;
                c[i]=i+3;
}
        struct  timeval start,end;
        gettimeofday(&start,NULL);
for(i=0;i<N-4;i+=4){
            c[i]=c[i]+a[i]*b[i];
            c[i+1]=c[i+1]+a[i+1]*b[i+1];
            c[i+2]=c[i+2]+a[i+2]*b[i+2];
            c[i+3]=c[i+3]+a[i+3]*b[i+3];
        }
           for(;i<N;i++)
               c[i]=c[i]+a[i]*b[i];
        gettimeofday(&end,NULL);
        double timeuse=(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1000000.0;
        printf("time=%f\n",timeuse);
        return 0;
}