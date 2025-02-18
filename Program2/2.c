#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

// Function to initialize a matrix with random values
void init(int *P, int N) {
    // Initialize a matrix P of size N x N with random values between 0 and 99
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            P[i*N + j] = rand() % 100;  // Assign random values between 0 and 99
        }
    }
}

// Function to display the matrix (for debugging/verification)
void display(int *P, int N, char c) {
    printf("The contents of matrix %c are:\n", c);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%d\t", P[i*N + j]);  // Print each element in the matrix
        }
        printf("\n");
    }
}

// Function to perform matrix multiplication
void process(int n, int tnum) {
    // Allocate memory for matrices A, B, and C (all NxN)
    int *A = malloc(sizeof(int) * n * n);
    int *B = malloc(sizeof(int) * n * n);
    int *C = malloc(sizeof(int) * n * n);

    // Initialize matrices A and B with random values
    init(A, n);
    init(B, n);

    // Start timing the matrix multiplication
    double t = omp_get_wtime();

    // Parallelize the matrix multiplication using OpenMP
    #pragma omp parallel for num_threads(tnum)
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i*n + j] = 0;  // Initialize the result matrix entry to 0
            for(int k = 0; k < n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];  // Matrix multiplication logic
            }
        }
    }

    // Calculate the time taken for the matrix multiplication
    t = omp_get_wtime() - t;
    printf("Time taken: %.4f seconds\n", t);

    // Display the matrices for verification
    printf("Input matrix A:\n");
    display(A, n, 'A');
    printf("Input matrix B:\n");
    display(B, n, 'B');
    printf("Resultant matrix C:\n");
    display(C, n, 'C');

    // Free allocated memory for the matrices
    free(A);
    free(B);
    free(C);
}

int main(int argc, char *argv[]) {
    // Ensure correct number of arguments are provided
    if(argc != 3) {
        printf("Usage: %s <matrix size> <number of threads>\n", argv[0]);
        return 1;  // Exit with error if arguments are missing
    }

    // Parse the arguments for matrix size (n) and number of threads (tnum)
    int n = atoi(argv[1]);
    int tnum = atoi(argv[2]);

    // Call the process function to perform matrix multiplication
    process(n, tnum);

    return 0;
}
