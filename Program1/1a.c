#include<stdio.h>  // Standard I/O library for printf
#include<stdlib.h> // Standard library for atoi and rand
#include<omp.h>    // OpenMP library for parallelization

// Function to perform the Monte Carlo simulation
void process(int iterations, int tnum) {
    int x = 0, y = 0;  // Variables for random coordinates (x, y)
    int N = 0;         // Counter for points inside the circle
    double t = omp_get_wtime();  // Start the timer for the computation

    // OpenMP parallel for loop
    #pragma omp parallel for num_threads(tnum) private(x, y) reduction(+:N)
    for (int i = 0; i < iterations; i++) {
        // Generate random (x, y) coordinates in the range [-50, 50]
        x = rand() % 100 - 50; // Random value between -50 and 49
        y = rand() % 100 - 50; // Random value between -50 and 49

        // Check if the point lies inside the circle of radius 50
        if (x * x + y * y <= 2500) {
            N++;  // Increment the counter if the point is inside the circle
        }
    }

    // Calculate the time taken for the computation
    t = omp_get_wtime() - t;
    printf("%.4f\t", t);  // Print the computation time to 4 decimal places
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        // If not, print usage information and exit
        printf("Usage: %s <iterations> <threads>\n", argv[0]);
        return 1;
    }

    // Parse the number of iterations and threads from the command line arguments
    int iterations = atoi(argv[1]);  // Convert first argument to integer (number of iterations)
    int tnum = atoi(argv[2]);        // Convert second argument to integer (number of threads)

    // Call the process function with the parsed arguments
    process(iterations, tnum);

    return 0;  // Return 0 to indicate successful execution
}
