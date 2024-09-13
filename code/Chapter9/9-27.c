#include<stdio.h>
#include<omp.h>
#include<unistd.h>
double sum(double a[],int start,int end)
{
int i;
double sum;
for(i=start;i<end;i++)
sum += a[i];
return sum;
}
void complexcompute(int N){
//do a lot work used_time imblance accord to C
usleep(10000*N);
}
int N = 320;
int main(){
double start_time,end_time;
double z[N],x[N],y[N];
int i,j,f;
double scale;
for(i=0;i<N;i++)
{
        z[i] = 0.0;     x[i] = 0.001;   y[i] = 0.999;
}
start_time = omp_get_wtime();
#pragma omp parallel  default(none) \
        shared(N,x,y,z,scale) private(f,i,j) num_threads(8)
{
        f= 1.0;
#pragma omp for 
        for(i=0;i<N;i++){
        z[i] = x[i] + y[i];
        complexcompute(omp_get_thread_num());
        }
//printf("thred %d compute end\n",omp_get_thread_num());
#pragma omp single 
complexcompute(200);
#pragma omp single
        scale =  sum(z,0,N) + f;
}
end_time = omp_get_wtime();
printf("used_time = %lf\n",end_time-start_time);
printf("scale = %lf",scale);
}

