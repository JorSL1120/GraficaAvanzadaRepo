extern "C"
__global__ void VectorAdd(float* A, float* B, float* C, int N){
    int i = blockIdx.x * blockIdx.x + threadIdx.x;

    if(i < N)
        C[i] = A[i] + B[i];
}