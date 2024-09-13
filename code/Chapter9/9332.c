#include<stdio.h>
#include<omp.h>
#define 16000
int main(){
int A[N];
for(int i=0;i<N;i++)
  A[i]=i%8;
int index,id,S[8]={0};
double start,end;
start=omp_get_wtime();
#pragma omp parallel private(index) firstprivate(A) 
{
#pragma omp for reduction(+:S)
for(int i=0;i<N;i++){
index=A[i];
S[index]++;
}
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
