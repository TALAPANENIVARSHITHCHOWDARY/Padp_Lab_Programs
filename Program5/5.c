#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 100  // Maximum size of each message
char messages[5][MSG_SIZE] = { "Hello", "RVCE", "CSE", "Department", "Bangalore" };

int main(int argc, char *argv[]) {
    int rank, num_processes;  // Rank of each process and total number of processes

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    
    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    // Ensure exactly 4 processes are running
    if (num_processes != 4) {
        if (rank == 0) {  // Only process 0 prints the error message
            printf("Number of processes is not equal to 4. Exiting..\n");
        }
        MPI_Finalize();  // Clean up MPI environment
        exit(1);
    }

    if (rank == 0) {
        // Process with rank 0 will receive messages from other processes
        char temp[MSG_SIZE];  // Buffer to store the received message
        for (int i = 1; i < num_processes; i++) {
            // Receive message from each process (rank 1 to 3)
            MPI_Recv(&temp, MSG_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // Print the message received
            printf("Message received from process %d: %s\n", i, temp);
        }
    } else {
        // Processes with rank 1, 2, and 3 send their messages to process 0
        char temp[MSG_SIZE];
        strcpy(temp, messages[rank - 1]);  // Select the message based on rank (rank-1 index)
        
        // Send the message to process 0
        MPI_Send(&temp, strlen(temp) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD); 
        // NOTE: `strlen(temp) + 1` ensures the null character is sent
    }

    // Clean up the MPI environment
    MPI_Finalize();
    return 0;
}
