#include <iostream>
#include <cuda.h>
using namespace std;

__global__ void vectorAdd(int* A, int* B, int* C, int n) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < n)
        C[id] = A[id] + B[id];
}

int main() {
    int n = 5;
    int size = n * sizeof(int);
    int h_A[] = {1, 2, 3, 4, 5};
    int h_B[] = {10, 20, 30, 40, 50};
    int h_C[n];
    int *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
    vectorAdd<<<1, n>>>(d_A, d_B, d_C, n);
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    cout << "Result Vector: ";
    for (int i = 0; i < n; i++) cout << h_C[i] << " ";
    cout << endl;
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    return 0;
}
