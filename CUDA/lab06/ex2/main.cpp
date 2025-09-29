#include <vector>
#include <iostream>
#include <cuda_runtime.h>
#include <random>

__global__ void custommath(int* vect, int* result, int val){

    int pos = blockIdx.x * blockDim.x + threadIdx.x;
    
    if(pos<val){
        result[pos]= (vect[pos]*vect[pos])+(2*vect[pos])+1;
    }
}

int randomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen);
}

int main(){

    std::vector<int> vect(10);
    std::vector<int> resultvect(10);
    int *vectpt;
    int *vectresult;

    for (size_t i = 0; i < 10; i++)
    {
        vect[i]= randomint();
    }
    cudaMalloc((void **) &vectpt, 10*sizeof(int));
    cudaMalloc((void **) &vectresult, 10*sizeof(int));
    cudaMemcpy(vectpt, vect.data(), 10*sizeof(int), cudaMemcpyHostToDevice);
    
    int blocksize=256;
    dim3 block = (blocksize);
    dim3 grid = ((10*blocksize-1)/blocksize);
    custommath<<<grid, block>>>(vectpt, vectresult, 10);
    cudaDeviceSynchronize();
    cudaMemcpy(resultvect.data(), vectresult, 10*sizeof(int), cudaMemcpyDeviceToHost);

    for(auto &val : resultvect){
        std::cout<<val<<" ";
    }

    cudaFree(vectresult);
    cudaFree(vectpt);
    return 0;
}