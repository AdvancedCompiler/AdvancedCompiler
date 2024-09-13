/*this test compelity for ROCBLAS*/

#include <iostream>
#include <vector>
#include "hip/hip_runtime_api.h"
#include "rocblas.h"
//#include <rocblas-auxiliary.h>
//#include <rocblas-functions.h>

using namespace std;
int main()
{
    rocblas_int n = 10240;
    float alpha = 10.0;
    vector<float> hx(n);
    vector<float> hz(n);
    float* dx;
    rocblas_handle handle;
    rocblas_create_handle(&handle);
    hipMalloc(&dx, n * sizeof(float));
    srand(1);
    for( int i = 0; i < n; ++i )
    {
        hx[i] = rand() % 10 + 1;  
    }
    hipMemcpy(dx, hx.data(), sizeof(float) * n, hipMemcpyHostToDevice);
    rocblas_status status = rocblas_sscal(handle, n, &alpha, dx, 1);

    if(status == rocblas_status_success){
        cout << "status == rocblas_status_success" << endl;
    }
    else{
        cout << "rocblas failure: status = " << status << endl;
    }
    hipMemcpy(hx.data(), dx, sizeof(float) * n, hipMemcpyDeviceToHost);

    hipFree(dx);
    rocblas_destroy_handle(handle);
    return 0;
}
