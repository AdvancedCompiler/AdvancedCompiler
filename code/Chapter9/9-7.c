#include <stdio.h>
#include <omp.h>
#define N 2000
int A[N],B[N];
int main()
{
double start_time,end_time,used_time;
int flag=0;
start_time=omp_get_wtime();
#pragma omp parallel
{
	if(flag==1){
		#pragma omp for 
		for(int i=0;i<N;i++)
			A[i] = i;
		 } 
	else {
		#pragma omp for
		for(int i=0;i<N;i++)
			B[i] = i;
		 }
}
end_time=omp_get_wtime();
used_time=end_time-start_time;
printf("used_time=%lf seconds\n",used_time);
}
