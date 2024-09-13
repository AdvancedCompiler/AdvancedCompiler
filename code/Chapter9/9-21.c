#include<stdio.h>
#include<omp.h>
#include<unistd.h>
int main(){
int i,j;
double start_time,end_time,used_time;
start_time = omp_get_wtime();
#pragma omp parallel for private(i,j) collapse(2) num_threads(8)
for(i=0;i<4;i++)
	for(j=0;j<8;j++)
		usleep(10000);
end_time = omp_get_wtime();
used_time = end_time - start_time;
printf("used_time = %lf\n",used_time);
}

