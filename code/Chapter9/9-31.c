#include <stdio.h>
#include <omp.h>
#define N1 10000
#define N2 10000
#define min(a,b) ((a)<(b)?(a):(b))
double a[N1][N2];
int i,j,m;
int isync[256],mthreadnum,iam;
#pragma omp threadprivate(mthreadnum,iam)
void sync_left()
{
        int neighbour;
        if(iam>0&&iam<=mthreadnum)
        {
                neighbour=iam-1;
                while(isync[neighbour]==0)
                {
                        #pragma omp flush(isync)
                }
                isync[neighbour]=0;
                #pragma omp flush(isync,a)
        }
}
void sync_right()
{
        if(iam<mthreadnum)
        {
                while(isync[iam]==1)
                {
                        #pragma omp flush(isync)
                }
		#pragma omp flush(isync,a)
                isync[iam%(mthreadnum-1)]=1;
		#pragma omp flush(isync)
        }
}
int main()
{
	isync[0]=1;
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
        #pragma omp parallel default(shared) private(i,j,m) shared(a) num_threads(8)
        {
		mthreadnum=1;
                mthreadnum=omp_get_num_threads()+1;
			iam=1;
                iam=omp_get_thread_num()+1;
		    isync[iam]=0;
                #pragma omp barrier
                int b=9;
                for(int i=1;i<N1-1;i=i+b)
{
                        sync_left();
				#pragma omp for schedule(static) nowait
                        for(int j=1;j<N2-1;j++)
                        {
					
                                for(int m=i;m<min(i+b,N1-1);m++)
							{
                                        a[m][j]=0.25*(a[m-1][j]+a[m][j-1]+a[m+1][j]+a[m][j+1]);
						}
                        }
                        sync_right();
                }
        }
	end_time=omp_get_wtime();
      used_time=end_time-start_time;
	
	double sum=0;
	for(i=0;i<N1;i++)
	{
		for(j=0;j<N2;j++)
			sum+=a[i][j];
	}
	printf("sum=%lf,used_time=%lf seconds\n",sum,used_time);
}
