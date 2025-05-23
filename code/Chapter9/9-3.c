#include <stdio.h>
#include <omp.h>
#define N 2000
float A[N][N],B[N][N];
float C[N][N];
int main()
{
int i,j,k;
float sum=0.0;
double start_time,end_time,used_time;
for(i=0;i<N;i++)
{
        for(j=0;j<N;j++)
        {
                A[i][j]=i+1.0;
                B[i][j]=1.0;
                C[i][j]=0.0;
        }
}
start_time=omp_get_wtime();
for(i=0;i<N;i++)
        for(j=0;j<N;j++)
                for(k=0;k<N;k++)
                        C[i][j]+=A[i][k]*B[k][j];
end_time=omp_get_wtime();
used_time=end_time-start_time;
for(i=0;i<N;i++)
        for(j=0;j<N;j++)
                sum+=C[i][j];
printf("sum=%lf,used_time=%lf seconds\n",sum,used_time);
}

