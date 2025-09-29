#include <iostream>
#include <cuda_runtime.h>
#include <vector>
#include <random>

const int size = 10;

int randomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen);
}

__global__ void avgfun(int* input, double* output, int size){

    int pos= blockIdx.x*blockDim.x+threadIdx.x;
    if(pos<size){
        if(pos==0){
            output[pos] = (0+input[pos]+input[pos+1]) / 3.0;
        }else if(pos==size-1){
            output[pos] = (input[pos-1]+input[pos]+0) /3.0;
        }else{
            output[pos] = (input[pos-1]+input[pos]+input[pos+1])/3.0;
        }
        
    }
}

int main(){

    std::vector<int> input(size);
    std::vector<double> output(size);
    int *inputpt;
    double *outputpt;

    for(size_t i=0; i<size; i++){
        input[i] = randomint();
    }

    cudaMalloc((void **) &inputpt, size*sizeof(int));
    cudaMalloc((void **) &outputpt, size*sizeof(double));
    cudaMemcpy(inputpt, input.data(), size*sizeof(int), cudaMemcpyHostToDevice);

    int blocksize= 256;
    dim3 block= (blocksize);
    dim3 grid= ((size+blocksize-1)/blocksize);

    avgfun<<<grid, block>>>(inputpt, outputpt, size);
    cudaDeviceSynchronize();
    cudaMemcpy(output.data(), outputpt, size*sizeof(double), cudaMemcpyDeviceToHost);

    for(auto &val: output){
        std::cout<<val<<" ";
    }
    
    cudaFree(inputpt);
    cudaFree(outputpt);
    return 0;
}