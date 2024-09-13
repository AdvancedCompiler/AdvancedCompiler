#include <stdio.h>
#include <omp.h>
#define N 2000
int B[N];
void init_array_B(int* b){
	#pragma omp for
	for(int i=0;i<N;i++)
		b[i]=i;
}
int main()
{
	double start_time,end_time,used_time;
	start_time=omp_get_wtime();
	#pragma omp parallel
	init_array_B(B);
	end_time=omp_get_wtime();
	used_time=end_time-start_time;
	printf("used_time=%lf seconds\n",used_time);
}

