#include <stdio.h>
#include <omp.h>
#define N 2000
#define min(a, b) (((a) < (b)) ? (a) : (b))
float A[N][N],B[N][N];
float C[N][N];
int BLOCK_SIZE=256;
int main()
{
int i,j,k;
double start_time,end_time,used_time;
float sum=0.0;
for(i=0;i<N;i++)
	for(j=0;j<N;j++)
	{
		A[i][j]=i+1.0;
		B[i][j]=1.0;
                C[i][j]=0.0;
	}
start_time=omp_get_wtime();
#pragma omp parallel for private(i,j,k) shared(A,B,C) if(N>86) num_threads(12)    
for (int ii = 0; ii < N; ii += BLOCK_SIZE)
	for (int jj = 0; jj < N; jj += BLOCK_SIZE)
		for (int kk = 0; kk < N; kk+=BLOCK_SIZE)
			for (i = ii; i < min(ii+BLOCK_SIZE,N); i++)
				for (k = kk; k < min(kk+BLOCK_SIZE,N); k++){
					int s=A[i][k];
					for ( j = jj; j < min(jj+BLOCK_SIZE,N); j++){
						C[i][j]+= s*B[k][j];
                      			}
				}
end_time=omp_get_wtime();
used_time=end_time-start_time;
for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		sum+=C[i][j];
//printf("sum=%lf,used_time=%lf seconds\n",sum,used_time);
printf("%lf",used_time);
}

