#include <cuda_runtime.h>
#include <iostream>
#include <vector>
#include <random>

int n = 10;
std::vector<double> v1(n);
std::vector<double> v2(n);
std::vector<double> v3(n);

double getrandomnum(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_real_distribution (-100, 100) (gen);
}

__global__ void multiply(int *v1, int *v2, int *v3, int n){
    int pos = blockIdx.x*blockDim.x+threadIdx.x;
    if(pos<n){
        v3[pos] = v1[pos]*v2[pos];
    }
}

int main(){
    for(size_t i=0; i<n; i++){
        v1[i]= getrandomnum();
        v2[i] = getrandomnum();
    }

    int *v1ptr;
    int *v2ptr;
    int *v3ptr;

    cudaMalloc((void **) &v1ptr, n*sizeof(double));
    cudaMalloc((void **) &v2ptr, n*sizeof(double));
    cudaMalloc((void **) &v3ptr, n*sizeof(double));

    cudaMemcpy(v1ptr, v1.data(), n*sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(v2ptr, v2.data(), n*sizeof(double), cudaMemcpyHostToDevice);

    int blocksize = 256;
    dim3 block(blocksize);
    dim3 grid((n+blocksize-1)/blocksize);
    
    multiply<<<grid, block>>>(v1ptr, v2ptr, v3ptr, n);
    cudaDeviceSynchronize();
    cudaMemcpy(v3.data(), v3ptr, n*sizeof(double), cudaMemcpyDeviceToHost);

    int sum=0;
    for(auto &val : v3){
        sum+=val;
    }
    std::cout<<val;
    cudaFree(v1ptr);
    cudaFree(v2ptr);
    cudaFree(v3ptr);
}