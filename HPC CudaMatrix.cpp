#include <iostream>
#include <cuda.h>
using namespace std;

__global__ void matrixMul(int* A, int* B, int* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < N && col < N) {
        int sum = 0;
        for (int k = 0; k < N; k++) {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

int main() {
    int N = 2;
    int size = N * N * sizeof(int);
    int h_A[] = {1, 2, 3, 4};
    int h_B[] = {5, 6, 7, 8};
    int h_C[N * N];
    int *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
    dim3 threadsPerBlock(N, N);
    dim3 blocksPerGrid(1, 1);
    matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    cout << "Result Matrix:" << endl;
    for (int i = 0; i < N * N; i++) {
        cout << h_C[i] << " ";
        if ((i+1) % N == 0) cout << endl;
    }
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    return 0;
}f
