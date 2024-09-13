#include <stdio.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdlib.h>
#include "../common.h"

//block线程循环优化
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

//数据预取核函数
__global__ void MatrixMulKernel02_preload(float* A, float* B, float* C, int width)
{
	int tx = threadIdx.x;
	int bx=blockIdx.x;
	extern __device__ float data1[256];
	extern __device__ float data2[256];
	for(int i = tx; i < width; i += blockDim.x){
		data1[i] = A[bx * width + i];
		data2[i] = B[i * width + tx];
	}
   	 for (bx = blockIdx.x; bx < width; bx += gridDim.x){
		for (tx =  threadIdx.x; tx < width; tx += blockDim.x){
			float Pvalue1 = 0;
			for (int k = 0; k < width; k++){
				Pvalue1 += data1[k] * data2[k];
             }
				C[bx * width + tx] = Pvalue1;			
		}
	}
}

//主机端矩阵乘法运算
void MatrixMulOnHost_3(float *A, float *B, float *C, int width)
{
    int i, j, k;
    double temp = 0.0;
    float *B1;
    B1 = (float *)malloc(sizeof(float) * width * width);
    for (int i = 0; i < width; i++){
         for(int j = 0; j < width; j++){
              B1[i * width + j] = B[j * width +i];
          }
    }
    for (i = 0; i < width; i++){
         for (j = 0; j < width; j++){
             temp = 0.0;
             for (k = 0; k < width; k++){
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
    for (int i = 0; i < N; i++){
        if (abs(hostRef[i] - gpuRef[i]) > epsilon){
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

int main(void)
{
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));
	                          
	int Width = 1<<11;
	int size = Width*Width*sizeof(float); 
               
    float *M, *N, *P, *gpuRef1, *gpuRef2; 
    M = (float *)malloc(size);
    N = (float *)malloc(size); 
    P = (float *)malloc(size);
    gpuRef1 = (float *)malloc(size);
	gpuRef2 = (float *)malloc(size);
                            
    double iStart = seconds();
    //初始化示例数据
	for (int i = 0; i<Width; i++){
        for (int j = 0; j<Width; j++){
            M[i*Width+j] = 3.0 ;
            N[i*Width+j] = 3.0 ;			
		}
	}
    double iElaps = seconds() - iStart;
    printf("initialization: \t %f sec\n", iElaps);
                             
/*------------------主机端-------------------------------------------------------*/

/*----------------------MatrixMulOnHost_3--------------------------------*/    
    iStart = seconds();
    MatrixMulOnHost_3(M, N, P, Width);
    iElaps = seconds() - iStart;
    printf("MatrixMulOnHost_3 : \t %f sec\n", iElaps);

/*------------------设备端-------------------------------------------------------- */	
	float *Md, *Nd, *Pd;
	cudaMalloc((void**)&Md, size);
	cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&Nd, size);
	cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&Pd, size);
                              
	dim3 block(1024);
    dim3 grid((Width + block.x - 1) / block.x);                 

/*----------------------MatrixMulKernel02----------------------*/
	iStart = seconds();
	MatrixMulKernel02<<<grid,block,sizeof(float)*(Width)>>>(Md, Nd, Pd, Width);
	iElaps = seconds() - iStart;
	printf("MatrixMulKernel02 on device  <<< %d, %d>>>:\t %f sec\n",grid.x, block.x, iElaps);
 	cudaMemcpy(gpuRef1, Pd, size, cudaMemcpyDeviceToHost);
    checkResult(P, gpuRef1, Width);

/*------------------MatrixMulKernel02_preload-------------------*/
	iStart = seconds();
	MatrixMulKernel02_preload<<<grid,block,sizeof(float)*(Width)>>>(Md, Nd, Pd, Width);
	iElaps = seconds() - iStart;
	printf("MatrixMulKernel02_preload on device  <<< %d, %d>>>:\t %f sec\n",grid.x, block.x, iElaps);
 	cudaMemcpy(gpuRef2, Pd, size, cudaMemcpyDeviceToHost);
    checkResult(P, gpuRef2, Width);
                            
    cudaFree(M);
    cudaFree(N);
    cudaFree(P);
    cudaFree(gpuRef1);
	cudaFree(gpuRef2);
	cudaFree(Md);
	cudaFree(Nd);
	cudaFree(Pd);
	cudaDeviceReset();
	
	return 0;
}