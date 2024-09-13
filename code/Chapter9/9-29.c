#include <stdio.h>
#include <omp.h>
#define N1 10000
#define N2 10000
double a[N1][N2];
int i,j;
int main()
{
	for(i=0;i<N1;i++)
	{
		for(j=0;j<N2;j=j+4)
			a[i][j]=3;
		for(j=1;j<N2;j=j+4)
			a[i][j]=5;
		for(j=2;j<N2;j=j+4)
			a[i][j]=4;
		for(j=3;j<N2;j=j+4)
			a[i][j]=8;
		for(j=4;j<N2;j=j+5)
			a[i][j]=7;
	}
	double start_time,end_time,used_time;
	start_time=omp_get_wtime();
   	for(i=1;i<N1-1;i++)
	{
		for(j=1;j<N2-1;j++)
               	{
      		a[i][j]=0.25*(a[i-1][j]+a[i][j-1]+a[i+1][j]+a[i][j+1]);		
           	}
      	}
	end_time=omp_get_wtime();
      used_time=end_time-start_time;
	float sum=0;
		for(i=0;i<N1;i++)
	{
		for(j=0;j<N2;j++)
			{
				sum+=a[i][j];
				}
}
	printf("sum=%lf,used_time=%lf seconds\n",sum,used_time);
}
