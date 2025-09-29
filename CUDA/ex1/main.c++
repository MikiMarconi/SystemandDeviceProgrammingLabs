#include <iostream>
#include <random>
#include <vector>
#include <cuda_runtime.h>

std::vector<int> matrixA;
std::vector<int> matrixB;

__global__ void computemol(int* A, int* B, int rowA, int colsA, int rowB, int *C){

    int posx = blockIdx.x * blockDim.x + threadIdx.x;
    int posy = blockIdx.y * blockDim.y + threadIdx.y;

    int sum=0;
    for (size_t i = 0; i < colsA; i++)
    {
        sum+= A[posy*colsA+i]*B[i*colsA+posx];
    }
    C[posy*colsB+posx] = sum;
}

int getrandomint(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<int> (-100, 100) (gen);
}

int main(int argc, char** argv){

    int R = std::stoi(argv[1]);
    int L = std::stoi(argv[2]);
    int C = std::stoi(argv[3]);
    int *a_matrix;
    int *b_matrix;
    int *c_matrix;

    for (size_t i = 0; i < R*L; i++)
    { 
        matrixA.emplace_back(getrandomint());
    }
    
    for (size_t i = 0; i < L*C; i++)
    {
        matrixB.emplace_back(getrandomint());
    }

    cudaMalloc((void **) &a_matrix, R* L * sizeof(int));
    cudaMemcpy(a_matrix, matrixA.data(), R* L * sizeof(int), cudaMemcpyHostToDevice);
    cudaMalloc((void **) &b_matrix, L* C * sizeof(int));
    cudaMemcpy(b_matrix, matrixB.data(), L* C * sizeof(int), cudaMemcpyHostToDevice);
    cudaMalloc((void **) &c_matrix, C*R*sizeof(int));

    int blocksize=16;
    dim3 block(blocksize, blocksize);
    dim3 grid((C*blocksize-1)/blocksize, (R*blocksize-1)/blocksize);
    computemol<<<grid,block>>>(a_matrix, b_matrix, R, L, C, c_matrix);
}

