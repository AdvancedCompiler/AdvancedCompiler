#include <stdlib.h>
#include <clFFT.h>
int main(void){
    cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_mem bufX;
    float *X;
    cl_event event = NULL;
    int ret = 0;
    size_t N = 16;
    clfftPlanHandle planHandle;
    clfftDim dim = CLFFT_1D;
    size_t clLengths[1] = {N};

    err = clGetPlatformIDs( 1, &platform, NULL );
    err = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL );
    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext( props, 1, &device, NULL, NULL, &err );
    queue = clCreateCommandQueue( ctx, device, 0, &err );
    clfftSetupData fftSetup;
    err = clfftInitSetupData(&fftSetup);
    err = clfftSetup(&fftSetup);
    X = (float *)malloc(N * 2 * sizeof(*X));
    bufX = clCreateBuffer( ctx, CL_MEM_READ_WRITE, N * 2 * sizeof(*X), NULL, &err );
    err = clEnqueueWriteBuffer( queue, bufX, CL_TRUE, 0,N * 2 * sizeof( *X ), X, 0, NULL, NULL );
    err = clfftCreateDefaultPlan(&planHandle, ctx, dim, clLengths);
    err = clfftSetPlanPrecision(planHandle, CLFFT_SINGLE);
    err = clfftSetLayout(planHandle, CLFFT_COMPLEX_INTERLEAVED, CLFFT_COMPLEX_INTERLEAVED);
    err = clfftSetResultLocation(planHandle, CLFFT_INPLACE);
    err = clfftBakePlan(planHandle, 1, &queue, NULL, NULL);
    err = clfftEnqueueTransform(planHandle, CLFFT_FORWARD, 1, &queue, 0, NULL, NULL, &bufX, NULL, NULL);
    err = clFinish(queue);
    err = clEnqueueReadBuffer( queue, bufX, CL_TRUE, 0, N * 2 * sizeof( *X ), X, 0, NULL, NULL );
    clReleaseMemObject( bufX );
    free(X);
    err = clfftDestroyPlan( &planHandle );
    clfftTeardown( );
    clReleaseContext( ctx );
    return ret;
}
