#include<stdio.h>
#include<omp.h>
int main(){
int k=2, sum1=0,sum2=0;
#pragma omp parallel firstprivate(k) shared(sum1,sum2)
{
	# pragma omp for reduction(+: sum1)
	for (int i=0;i<10000;i++)
		sum1 += (k+i);
	#pragma omp single
	sum2 = sum1;
	k++;
	# pragma omp for reduction(+: sum2)
	for (int j=0;j<10000;j++)
		sum2 += (2*k+j);
	#pragma omp master
	printf("sum1=%d, sum2=%d\n", sum1, sum2); 
}
}
