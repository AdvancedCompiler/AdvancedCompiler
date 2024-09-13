#include<stdio.h>
#include<omp.h>
#define N 16000
int main(){
int A[N];
for(int i=0;i<N;i++)
  A[i]=i%8;
int index,id,S[5][8]={0};
double start,end;
start=omp_get_wtime();
#pragma omp parallel private(index,id) firstprivate(A) shared(S) num_threads(4)
{
id=omp_get_thread_num()+1;
#pragma omp for nowait
for(int i1=0;i1<N;i1++){
index=A[i1];
S[id][index]++;
}
#pragma omp critical
for(int j=0;j<8;j++)
S[0][j]+=S[id][j];
}
end = omp_get_wtime();
printf("%f\n",end-start);
//统计结果展示
//for(int i =0;i<8;i++)
//  printf("%d\n",S[0][i]);
}

