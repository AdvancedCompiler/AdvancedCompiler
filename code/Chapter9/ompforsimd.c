#include <stdio.h>
#include <omp.h>
#define N 2000
float A[N][N],B[N][N];
float C[N][N];
int main()
{
double start_time,end_time,used_time;
		for(int i=0;i<N;i++)
		{
			int t=i+1.0;
			for(int j=0;j<N;j++)
			{
				A[i][j]=t++;
				B[i][j]=1.0;
                		C[i][j]=0.0;
			}
		}
		float sum=0.0;
start_time=omp_get_wtime();
#pragma omp parallel num_threads(10)
#pragma omp for simd simdlen(8)
      	for(int i=0;i<N;i++)
		 	for(int j=0;j<N;j++)
		 	{
				for(int k=0;k<N;k++)
				 		C[i][j]+=A[i][k]*B[k][j];
			}
end_time=omp_get_wtime();
used_time=end_time-start_time;
for(int i=0;i<N;i++)
   	for(int j=0;j<N;j++)
        	sum+=C[i][j];
 printf("矩阵C所有元素和为sum=%lf，并行计算时间为：used_time=%lf seconds\n",sum,used_time);
}

