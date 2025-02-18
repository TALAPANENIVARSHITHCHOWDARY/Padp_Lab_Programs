#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

// Function to simulate Monte Carlo iterations
int process(int iter_num) {
    float x = 0, y = 0;
    int N = 0; // Count of points within the circle
    for (int i = 0; i < iter_num; i++) {
        x = (float)rand() / RAND_MAX; // Generate random x in [0, 1)
        y = (float)rand() / RAND_MAX; // Generate random y in [0, 1)
        if (x * x + y * y <= 1)       // Check if point is within the circle
            N++;
    }
    return N;
}

int main(int argc, char *argv[]) {
    // Check for valid number of arguments
    if (argc != 2) {
        printf("Invalid number of arguments. Usage: ./a.out <num_iterations>\n");
        return 1;
    }

    float t; // Timing variable
    int rank, num_processes; // MPI rank and total number of processes

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes); // Get total number of processes

    // Parse number of iterations per process from command line
    int N = atoi(argv[1]);
    if (N <= 0) {
        if (rank == 0) {
            printf("Error: Number of iterations must be positive.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Start timing and run simulation for this process
    srand(time(NULL) + rank); // Seed random number generator uniquely for each process
    t = MPI_Wtime();
    int res = process(N); // Perform Monte Carlo simulation for this process
    t = MPI_Wtime() - t;
    printf("Time taken by process %d is %.4f seconds\n", rank, t);

    if (rank == 0) {
        // Rank-0 (master) process collects results from all other processes
        int temp = 0; // Temporary variable to store results from other processes
        t = MPI_Wtime();
        for (int i = 1; i < num_processes; i++) {
            MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Receive results
            res += temp; // Accumulate results
        }
        t = MPI_Wtime() - t;
        printf("Time taken to gather results is %.4f seconds\n", t);

        // Calculate and print the approximate value of PI
        float PI = (float)(4 * res) / (num_processes * N);
        printf("Approximated value of PI is %.4f\n", PI);
    } else {
        // Worker processes send their results to the master process
        MPI_Send(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
