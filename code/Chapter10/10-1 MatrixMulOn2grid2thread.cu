#include <stdio.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdlib.h>
#include "../common.h"

__global__ void MatrixMulKernel01(float* Md, float* Nd, float* Pd, int width)
{
    int tx = threadIdx.x + blockIdx.x * blockDim.x;
    int bx = threadIdx.y + blockIdx.y * blockDim.y;
	int idx=bx*width+tx;
	int row=idx/width;
	int col=idx%width;
	
	if(row<width && col<width){
		float Pvalue = 0;
		for (int k = 0; k<width; k++)
		{
			float Mdelement = Md[row*width + k];
			float Ndelement = Nd[k*width + col];
			Pvalue += Mdelement * Ndelement;
                                 }
		Pd[row*width + col] = Pvalue;
	  }
}

void MatrixMulOnHost_3(float *A, float *B, float *C, int width)
{
    int i, j, k;
    double temp = 0.0;
    float *B1;
    B1 = (float *)malloc(sizeof(float) * width * width);
    for (int i = 0; i < width; i++)
    {
         for(int j = 0; j < width; j++)
         {
              B1[i * width + j] = B[j * width +i];
          }
    }
    for (i = 0; i < width; i++)
    {
         for (j = 0; j < width; j++)
         {
             temp = 0.0;
             for (k = 0; k < width; k++)
             {
                  temp += A[i * width + k] * B1[j * width +k];
             }    
             C[i * width + j] = temp;
           }
    }
    free (B1);
}

//结果检查
void checkResult(float *hostRef, float *gpuRef, const int N)
{
    double epsilon = 1.0E-8;
    bool match = 1;

    for (int i = 0; i < N; i++)
    {
        if (abs(hostRef[i] - gpuRef[i]) > epsilon)
        {
            match = 0;
            printf("host %f gpu %f\n", hostRef[i], gpuRef[i]);
            break;
        }
    }

    if (match)
        printf("Results match.\n\n");
    else
        printf("Results do not match.\n\n");
}


int main(void){
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));
	
    int Width = 1 << 10 ;
    int size = Width*Width*sizeof(float); 

    float *M, *N, *P, *gpuRef; 
    M = (float *)malloc(size);
    N = (float *)malloc(size); 
    P = (float *)malloc(size);
    gpuRef = (float *)malloc(size);
    
    double iStart = seconds();
    for (int i = 0; i<Width; i++){
        for (int j = 0; j<Width; j++){
            M[i*Width+j] = 2.0 ;
            N[i*Width+j] = 3.0 ;			
        }
    }
    double iElaps = seconds() - iStart;
    printf("initialization: \t %f sec\n", iElaps);

    iStart = seconds();
    MatrixMulOnHost_3(M, N, P, Width);
    iElaps = seconds() - iStart;
    printf("MatrixMulOnHost_3 : \t %f sec\n", iElaps);

    float *Md, *Nd, *Pd;
    cudaMalloc((void**)&Md, size);
    cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
    cudaMalloc((void**)&Nd, size);
    cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);
    cudaMalloc((void**)&Pd, size);

    int dimx = 32;
    int dimy = 32;
    dim3 block(dimx,dimy);
    dim3 grid((Width + block.x - 1) / block.x,  (Width + block.y - 1) / block.y);

    iStart = seconds();
    MatrixMulKernel03<<<grid,block>>>(Md, Nd, Pd, Width);
    iElaps = seconds() - iStart;
    printf("MatrixMulKernel03 on device  <<< (%d,%d), (%d,%d)>>>:\t %f sec\n",grid.x, grid.y, block.x, block.y, iElaps);
    cudaMemcpy(gpuRef, Pd, size, cudaMemcpyDeviceToHost);

    checkResult(P, gpuRef, Width);                                        

    cudaFree(M);
    cudaFree(N);
    cudaFree(P);
    cudaFree(gpuRef);
    cudaFree(Md);
    cudaFree(Nd);
    cudaFree(Pd);

    return 0;
}
