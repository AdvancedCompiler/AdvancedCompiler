#include<stdio.h>
#include<omp.h>
static long num_steps = 1000000;
double step;
int main()
{
int i;
double x,pi,sum;
double start_time,end_time;
step = 1.0/(double)num_steps;
start_time = omp_get_wtime();
for(i=0;i<num_steps;i++)
{
	x = (i+0.5)*step;
	sum+=4.0/(1.0+x*x);
}
pi=step*sum;
end_time = omp_get_wtime();
printf("pi=%15.13f,runtime = %lf\n",pi,end_time-start_time);
}
