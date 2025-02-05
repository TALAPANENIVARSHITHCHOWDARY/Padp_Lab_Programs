#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void init(int *P, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            P[i * N + j] = rand() % 100;
}

void display(int *P, int N, char ch) {
    printf("The Matrix %c:\n", ch);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d\t", P[i * N + j]);
        printf("\n");
    }
}

void process(int N, int tnum) {
    int *A = malloc(sizeof(int) * N * N);
    int *B = malloc(sizeof(int) * N * N);
    int *C = malloc(sizeof(int) * N * N);

    if (!A || !B || !C) {
        printf("Memory allocation failed\n");
        return;
    }

    init(A, N);
    init(B, N);

    double t = omp_get_wtime();
    #pragma omp parallel for num_threads(tnum)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
    t = omp_get_wtime() - t;
    printf("Time taken: %.4f seconds\n", t);

    // Uncomment to verify results
    // display(A, N, 'A');
    // display(B, N, 'B');
    // display(C, N, 'C');

    free(A);
    free(B);
    free(C);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <Matrix Size> <Number of Threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int tnum = atoi(argv[2]);

    process(N, tnum);
    return 0;
}
