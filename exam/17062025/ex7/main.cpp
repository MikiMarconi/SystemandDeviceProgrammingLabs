#include <iostream>
#include <cuda_runtime.h>
#include <vector>
#include <random>

int getrandomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen);
}

__global__ void multiplyandstore(int* v1, int* v2, int* mult, int n){
    int pos = blockIdx.x * blockDim.x +threadIdx.x;
    if(pos<n){
        mult[pos] = v1[pos]*v2[pos];
    }
}

int main(){
    int n = 10;
    std::vector<int> v1(n);
    std::vector<int> v2(n);
    std::vector<int> mult(n);
    int *v1pt;
    int *v2pt;
    int *multpt;

    for(size_t i = 0; i<n; i++){
        v1[i]= getrandomint();
        v2[i]= getrandomint();
    }

    cudaMalloc((void **) &v1pt, n*sizeof(int));
    cudaMalloc((void **) &v2pt, n*sizeof(int));
    cudaMalloc((void **) &multpt, n*sizeof(int));
    cudaMemcpy(v1pt, v1.data(), n*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(v2pt, v2.data(), n*sizeof(int), cudaMemcpyHostToDevice);

    int blocksize = 256;
    dim3 block(blocksize);
    dim3 grid((n+blocksize-1)/blocksize);

    multiplyandstore<<<grid, block>>>(v1pt, v2pt, multpt, n);
    cudaDeviceSynchronize();
    cudaMemcpy(mult.data(), multpt, n*sizeof(int), cudaMemcpyDeviceToHost);

    int sum=0;
    for(auto& val: mult){
        sum+= val;
    }

    std::cout<<sum<<std::endl;
    cudaFree(multpt);
    cudaFree(v1pt);
    cudaFree(v2pt);
    return 0;
}