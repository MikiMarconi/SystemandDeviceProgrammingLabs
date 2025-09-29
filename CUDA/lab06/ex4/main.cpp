#include <iostream>
#include <cuda_runtime.h>
#include <vector>
#include <random>

const int size= 10;

int randomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (0, 100) (gen);
}

__global__ void setbins(int* input, int* output, int size){

    int pos = blockIdx.x*blockDim.x+threadIdx.x;
    if(pos<size){
        int index = input[pos]/10;
        atomicAdd(&output[index], 1);
    }
}

int main(){
    std::vector<int> vectorinput(size);
    std::vector<int> vectorbins(size);
    int *inputpt;
    int *binspt;

    for(size_t i=0; i<size; i++){
        vectorinput[i]= randomint();
    }

    cudaMalloc((void **) &inputpt, size*sizeof(int));
    cudaMalloc((void **) &binspt, size*sizeof(int));
    cudaMemcpy(inputpt, vectorinput.data(), size*sizeof(int), cudaMemcpyHostToDevice);

    int blocksize= 256;
    dim3 block(blocksize);
    dim3 grid((size+blocksize-1)/blocksize);

    setbins<<<grid, block>>>(inputpt, binspt, size);
    cudaDeviceSynchronize();
    cudaMemcpy(vectorbins.data(), binspt, size*sizeof(int), cudaMemcpyDeviceToHost);

    for(auto& val: vectorinput){
        std::cout<<val<<" ";
    }
    std::cout<<std::endl;

    for(auto& val: vectorbins){
        std::cout<<val<<" ";
    }



}