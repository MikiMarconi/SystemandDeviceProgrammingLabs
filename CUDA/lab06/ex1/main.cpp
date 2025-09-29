#include <iostream>
#include <cuda_runtime.h>
#include <vector>

const int ARRAY_SIZE= 10;

__global__ void gpu_saxpy(double* vectx, double* vecty, double* result, int arrsize, int a){
    int pos = blockIdx.x * blockDim.x+ threadIdx.x;
    if(pos<arrsize){
        result[pos] = (a*vectx[pos])+ vecty[pos];
    }
}


int main(int argc, char** argv){
    std::vector<double> x(ARRAY_SIZE);
    std::vector<double> y(ARRAY_SIZE);
    std::vector<double> result(ARRAY_SIZE);
    double* vectx;
    double* vecty;
    double* resultpt;

    const int a = std::atoi(argv[1]); 

    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        if(i%2==0){
            x[i] = 0.1;
            y[i] = 0.1;
        }else{
            x[i] = 0.2;
            y[i] = 0.2;
        }
        
    }

    cudaMalloc((void **) &vectx, ARRAY_SIZE*sizeof(int));
    cudaMalloc((void **) &vecty, ARRAY_SIZE*sizeof(int));
    cudaMalloc((void **) &resultpt, ARRAY_SIZE*sizeof(int));

    cudaMemcpy(vectx, x.data(), ARRAY_SIZE*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(vecty, y.data(), ARRAY_SIZE*sizeof(int), cudaMemcpyHostToDevice);

    int blocksize=256;
    dim3 block(blocksize);
    dim3 grid((ARRAY_SIZE+blocksize-1)/blocksize);

    gpu_saxpy<<<grid, block>>>(vectx, vecty, resultpt, ARRAY_SIZE, a);
    cudaDeviceSynchronize();
    cudaMemcpy(result.data(), resultpt, ARRAY_SIZE*sizeof(int), cudaMemcpyDeviceToHost);
    
    for(auto& v: result){
        std::cout<<v<<" ";
    }

    cudaFree(vectx);
    cudaFree(vecty);
    cudaFree(resultpt);
}