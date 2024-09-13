#include <stdio.h>
#include <omp.h>
#define N 2000
int A[N];
void init_array_A(int* a){
	#pragma omp parallel for
	for(int i=0;i<N;i++)
		a[i]=i;
}
int main()
{
double start_time,end_time,used_time;
start_time=omp_get_wtime();
init_array_A(A);
end_time=omp_get_wtime();
used_time=end_time-start_time;
printf("used_time=%lf seconds\n",used_time);
}

