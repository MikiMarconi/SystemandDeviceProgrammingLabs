#include <iostream>
#include <cuda_runtime.h>
#include <vector>
#include <random>

const int n=16;
int randomnum(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen); 
}

__global__ void sum(int* A, int* B, int n){
    int pos= blockIdx.x*blockDim.x+threadIdx.x;
    if(pos<n){
        int i;
        int sum=0;
        for(i=0; i<pos; i++){
            sum+= A[i];
        }
        B[pos]= sum;
    }
}

int main(){
    std::vector<int> vectorint(n);
    std::vector<int> vectorresult(n);
    int blocksize=256;
    int i;
    for(i=0; i<n; i++){
        vectorint[i]=randomnum();
    }

    int* vectA;
    int* vectB;

    cudaMalloc((void **) &vectA, n*sizeof(int));
    cudaMemcpy(vectA, vectorint.data(), n*sizeof(int), cudaMemcpyHostToDevice);
    cudaMalloc((void **) &vectB, n*sizeof(int));

    dim3 block(blocksize);
    dim3 blockspergrid((n+blocksize-1)/blocksize);

    sum<<<blockspergrid, block>>>(vectA, vectB, n);
    cudaDeviceSynchronize();

    cudaMemcpy(vectorresult.data(), vectB, n*sizeof(int), cudaMemcpyDeviceToHost);

    for(auto& v: vectorresult){
        std::cout<<v<<" ";
    }

    cudaFree(vectA);
    cudaFree(vectB);
    return 0;
}