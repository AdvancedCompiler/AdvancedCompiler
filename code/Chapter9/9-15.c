#include<stdio.h>
#include<omp.h>
#define Nthreads 4
static long num_steps = 1000000;
double step;
int main(){
int i,j;
double pi,start_time,used_time;
double sum[Nthreads]={0.0};
step  = 1.0/(double) num_steps;
start_time = omp_get_wtime();
#pragma omp parallel num_threads(4)
{
int i;
int id = omp_get_thread_num();
double x;
#pragma omp for 
	for(i=0;i<num_steps;i++){
	x = (i+0.5)*step;
	sum[id] += 4.0/(1.0+x*x);
	}
}
pi = 0.0;
for(i=0;i<Nthreads;i++)
pi += sum[i];
pi = step*pi;
used_time = omp_get_wtime() - start_time;
printf("pi = %15.13f in \%f seconds\n",pi,used_time); 
} 
