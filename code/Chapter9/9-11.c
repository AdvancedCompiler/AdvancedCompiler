#include<stdio.h>
#include<omp.h>
int main(){
int k=2, sum1=0,sum2=0;
double start_time,end_time,used_time;
start_time = omp_get_wtime();
#pragma omp parallel firstprivate(k) 
{
        # pragma omp for reduction(+: sum1)
        for (int i=0;i<10000;i++)
                sum1 += (k+i);

        # pragma omp for reduction(+: sum2)
        for (int j=0;j<10000;j++)
                sum2 += (k*2+j);
}
end_time = omp_get_wtime();
used_time = end_time - start_time;
printf("used_time = %lf\n",used_time);
printf("sum1 = %d,sum2 = %d\n",sum1,sum2);
}

