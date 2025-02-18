#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <float.h>

// Function to get the maximum of two doubles
double get_max(double x, double y) {
    if (x > y)
        return x;
    return y;
}

// Function to print a 2D matrix stored in a flattened 1D array
void print_arr(double *A, int N) {	
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%.2f\t", A[N * i + j]);
        printf("\n");
    }
}

// Main function
// Arguments: matrix size (n), maximum iterations (max_iter), and tolerance (tol)
int main(int argc, char *argv[]) {
    struct timespec start, end;  // Variables to measure execution time
    double elapsed_time;         // Store elapsed time
    
    int max_iter, n, n2;         // max_iter: maximum iterations; n: matrix size; n2: padded size
    double tol, max_diff = DBL_MAX;  // tol: convergence tolerance; max_diff: maximum difference between iterations

    // Parse command-line arguments
    if (argc != 4) {
        printf("Usage: ./a.out <matrix_size> <max_iterations> <tolerance>\n");
        return -1;
    }
    n = atoi(argv[1]);          // Matrix size
    max_iter = atoi(argv[2]);   // Maximum number of iterations
    tol = atof(argv[3]);        // Convergence tolerance
    printf("Matrix Size: %d\tMax Iterations: %d\tTolerance: %lf\n", n, max_iter, tol);

    n2 = n + 2;  // Add padding to matrix (for boundary cells)

    // Allocate memory for the matrix and a temporary matrix (both with padding)
    double restrict *T, *T_new;  // Restrict keyword helps compilers optimize memory usage
    double *temp = NULL;         // Temporary pointer for swapping matrices
    T = (double *)malloc(sizeof(double) * n2 * n2);
    T_new = (double *)malloc(sizeof(double) * n2 * n2);

    // Check for successful memory allocation
    if (T == NULL || T_new == NULL) {
        printf("\nError: Not enough memory to allocate matrices.\n");
        exit(0);
    }

    // Initialize boundary conditions (bottom and right edges)
    for (int i = 1; i <= n; i++) {
        T[n * n2 + i] = (i * 100) / (n + 1); // Bottom boundary
        T[n2 * i + n] = (i * 100) / (n + 1); // Right boundary
    }

    // Uncomment the following lines if you want to see the initial matrices
    // print_arr(T, n2); 
    // printf("\n");

    // Start measuring time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Main computation using OpenACC to parallelize the workload
    #pragma acc kernels
    {
        // Copy data to GPU for parallel processing
        #pragma acc data copy(T[0:n2*n2], T_new[0:n2*n2])
        for (int x = 1; x <= max_iter && max_diff > tol; x++) {  // Iterate until convergence or max iterations
            max_diff = 0;  // Reset max_diff for each iteration

            // Divide the matrix into smaller tiles (32x32 blocks) and calculate in parallel
            #pragma acc parallel loop tile(32,32) reduction(max:max_diff)
            for (int i = 1; i <= n; i++) {       // Traverse rows
                for (int j = 1; j <= n; j++) {   // Traverse columns
                    // Update each cell using the average of its four neighbors
                    T_new[n2 * i + j] = 0.25 * (T[n2 * i + j - 1] + T[n2 * i + j + 1] +
                                              T[(i - 1) * n2 + j] + T[(i + 1) * n2 + j]);

                    // Calculate the maximum difference between old and new values
                    max_diff = get_max(max_diff, fabs(T_new[n2 * i + j] - T[n2 * i + j]));
                }
            }

            // Swap the pointers to avoid copying data between T and T_new
            temp = T;
            T = T_new;
            T_new = temp;

            // Uncomment to debug the matrix after each iteration
            // print_arr(T, n2);
            // printf("\n");
        }
    }

    // Stop measuring time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time in seconds
    elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time taken = %.4fs\n", elapsed_time);

    // Uncomment to print the final matrix
    // print_arr(T, n2);

    // Free allocated memory
    free(T);
    free(T_new);

    return 0;
}
