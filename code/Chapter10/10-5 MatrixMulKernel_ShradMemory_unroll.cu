#include <stdio.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdlib.h>
#include "../common.h"


//共享内存优化核函数
__global__ void MatrixMulKernel_ShradMemory(float* Md, float* Nd, float* Pd, int width){
	extern __shared__ float data[];
	const int tid = threadIdx.x;
	const int row = blockIdx.x;
	int i, j;

	for(i = tid; i < width; i += blockDim.x){
		data[i] = Md[row * width + i];
	}
	__syncthreads();
	double tmp = 0.0;
	for(j = tid; j < width; j += blockDim.x){
		tmp = 0.0;
		for(i = 0; i < width; i++){
			tmp += data[i] * Nd[i * width + j];
		}
		Pd[row * width + j] = tmp;
	}
}


//循环展开核函数
__global__ void MatrixMulKernel_ShradMemory_unroll2(float* Md, float* Nd, float* Pd, int width){
	extern __shared__ float data[];
	const int tid = threadIdx.x;
	const int row = blockIdx.x;
	int i, j;

	for(i = tid; i < width; i += blockDim.x){
		data[i] = Md[row * width + i];
	}
	__syncthreads();
	double tmp = 0.0;
	for(j = tid; j < width; j += blockDim.x){
		tmp = 0.0;
		for(i = 0; i < width/2; i++){
			tmp += data[i] * Nd[i * width + j];
			tmp += data[i+1] * Nd[(i+1) * width + j]; 
			
		}
		Pd[row * width + j] = tmp;
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

//主机端矩阵乘法运算展开循环
void MatrixMulOnHost_3_unroll2(float *A, float *B, float *C, int width)
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
             for (k = 0; k < width/2; k++){
                  temp += A[i * width + k] * B1[j * width +k];
                  temp += A[i * width + k+1] * B1[j * width +k+1];
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

    iStart = seconds();
    MatrixMulOnHost_3_unroll2(M, N, P, Width);
    iElaps = seconds() - iStart;
    printf("MatrixMulOnHost_3_unroll2 : \t %f sec\n", iElaps);

/*------------------设备端-------------------------------------------------------- */	
	float *Md, *Nd, *Pd;
	cudaMalloc((void**)&Md, size);
	cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&Nd, size);
	cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&Pd, size);
                
	//int dimx = 32;
    //int dimy = 32;
    //dim3 block(dimx,dimy);
    //dim3 grid((Width + block.x - 1) / block.x,  (Width + block.y - 1) / block.y);                  
	dim3 block(1024);
    dim3 grid((Width + block.x - 1) / block.x);                 

/*----------------------MatrixMulKernel_ShradMemory----------------------*/
	iStart = seconds();
	MatrixMulKernel_ShradMemory<<<grid,block,sizeof(float)*(Width)>>>(Md, Nd, Pd, Width);
	iElaps = seconds() - iStart;
	printf("MatrixMulKernel_ShradMemory on device  <<< %d, %d>>>:\t %f sec\n",grid.x, block.x, iElaps);
 	cudaMemcpy(gpuRef1, Pd, size, cudaMemcpyDeviceToHost);
    checkResult(P, gpuRef1, Width);

/*------------------MatrixMulKernel_ShradMemory_unroll2-------------------*/
	iStart = seconds();
	MatrixMulKernel_ShradMemory_unroll2k<<<grid,block,sizeof(float)*(Width)>>>(Md, Nd, Pd, Width);
	iElaps = seconds() - iStart;
	printf("MatrixMulKernel_ShradMemory_unroll2 on device  <<< %d, %d>>>:\t %f sec\n",grid.x, block.x, iElaps);
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