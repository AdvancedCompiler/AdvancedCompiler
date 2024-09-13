#include <stdio.h>
#include <omp.h>
#define N 2000
int A[N],B[N];
int main()
{
double start_time,end_time,used_time;
start_time=omp_get_wtime();
int flag=0,i;
if (flag==0){
	#pragma omp parallel for private(i)
	for(i=0;i<N;i++)
		A[i] = i;
	flag=1;
 	} 
else{
	#pragma omp parallel for private(i)
	for(i=0;i<N;i++)
		B[i] = i;
	}
end_time=omp_get_wtime();
used_time=end_time-start_time;
printf("used_time=%lf seconds\n",used_time);
}
