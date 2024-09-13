#include <stdio.h>
#include <malloc.h>
#include <mkl_cblas.h>
#define N 10
void initVector(MKL_Complex16*v){
  for(int i=0;i<N;i++){
    v[i].real=-i*1.0f;
      v[i].imag=i*1.0f;
  }
}
int main(int argc, char* argv[]){
    MKL_Complex16*vector = (MKL_Complex16*)malloc(sizeof(MKL_Complex16)*N);
    initVector(vector);
    double ret3 = cblas_dzasum(N,vector,1);
    printf("Result of sasum:%lf\n",ret3);
    free(vector);
    return 0;
}

