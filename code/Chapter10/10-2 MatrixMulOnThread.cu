#include <stdio.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdlib.h>
#include "../common.h"

__global__ void MatrixMulKernel01(float* A, float* B, float* C, int width)
{
    	int tx = threadIdx.x;
    	int bx = blockDim.x;
	int idx=bx*width+tx;
	int row=idx/width;
	int col=idx%width;
	if(row<width && col<width){
		float Pvalue = 0;
		for (int k = 0; k<width; k++){
			float Mdelement = A[row*width + k];
			float Ndelement = B[k*width + col];
			Pvalue += Mdelement * Ndelement;
         }
		C[row*width + col] = Pvalue;
	  }
}
__global__ void MatrixMulKernel02(float* A, float* B, float* C, int width)
{
	int tx = threadIdx.x;
	int bx=blockIdx.x;
    for (bx = blockIdx.x; bx < width; bx += gridDim.x){
		for (tx  =  threadIdx.x; tx < width; tx += blockDim.x){
			float Pvalue = 0;
			for (int k = 0; k < width; k++){
				float Mdelement = A[bx * width + k];
				float Ndelement = B[k * width + tx];
				Pvalue += Mdelement * Ndelement;
            }
			C[bx * width + tx] = Pvalue;	
		}
	}
}

void MatrixMulOnHost(float *A, float *B, float *C, int width)
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
    //矩阵元素
int Width = 1 << 10 ;
int size = Width*Width*sizeof(float); 

float *M, *N, *P, *gpuRef01, *gpuRef02; 
M = (float *)malloc(size);
N = (float *)malloc(size); 
P = (float *)malloc(size);
gpuRef01 = (float *)malloc(size);
gpuRef02 = (float *)malloc(size);
double iStart = seconds();
//初始化示例数据
for (int i = 0; i<Width; i++){
for (int j = 0; j<Width; j++){
      M[i*Width+j] = 2.0 ;
      N[i*Width+j] = 3.0 ;			
}
}
double iElaps = seconds() - iStart;
printf("initialization: \t %f sec\n", iElaps);
//矩阵乘在主机端运行
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

dim3 block(1024);
dim3 grid((Width + block.x - 1) / block.x);                  
//矩阵乘在设备端运行
iStart = seconds();
MatrixMulKernel01<<<grid,block>>>(Md, Nd, Pd, Width);
iElaps = seconds() - iStart;
printf("MatrixMulKernel01 on device  <<< %d,%d>>>:\t %f sec\n",grid.x, block.x, iElaps);
cudaMemcpy(gpuRef01, Pd, size, cudaMemcpyDeviceToHost);
checkResult(P, gpuRef01, Width);

iStart = seconds();
MatrixMulKernel02<<<grid , block>>>(Md, Nd, Pd, Width);
iElaps = seconds() - iStart;
printf("MatrixMulKernel02 on device  <<< %d,%d>>>:\t %f sec\n",grid.x, block.x, iElaps);
cudaMemcpy(gpuRef02, Pd, size, cudaMemcpyDeviceToHost);
checkResult(P, gpuRef02, Width);

cudaFree(M);
cudaFree(N);
cudaFree(P);
cudaFree(gpuRef1);
cudaFree(gpuRef2);
cudaFree(Md);
cudaFree(Nd);
cudaFree(Pd);
return 0;
}
