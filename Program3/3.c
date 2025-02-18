#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<stdbool.h>
#include<math.h>

// Function to print prime numbers in the array X
void print_arr(bool* X ,int n){
    for(long i=2; i<n; i++){  // Start from 2, as 0 and 1 are not prime
        if(X[i] == 1)  // If X[i] is 1, it means i is a prime
            printf("%ld\t", i);  // Print the prime number i
    }
    printf("\n");
}

// Sieve of Eratosthenes (Unfriendly to Cache) - Simple Implementation
void sieve_unfriendly(int n){
    bool* X = malloc(sizeof(bool) * n);  // Boolean array to store sieve status
    int ret_val = 0;  // To store the count of primes
    for(int i = 2; i < n; i++) {
        X[i] = 1;  // Initialize all numbers as prime (1)
    }
    
    double t = omp_get_wtime();  // Start the timer for performance measurement

    // Sieve the numbers using the classic method
    for(int i = 2; i < n; i++) {
        if(X[i] == 0) {  // Skip if already marked as non-prime
            continue;
        }
        // Mark multiples of i as non-prime (0)
        for(int j = 2 * i; j < n; j += i) {
            X[j] = 0;
        }
    }

    t = omp_get_wtime() - t;  // Stop the timer
    printf("Time taken (unfriendly cache): %.4f seconds\n", t);

    // Print the primes found (optional, can be commented out for large numbers)
    // print_arr(X, n);
    
    // Count the primes
    for(int i = 2; i < n; i++) {
        if(X[i] == 1) {  // If X[i] is 1, it's a prime
            ret_val++;
        }
    }

    free(X);  // Free the allocated memory
    printf("Number of primes: %d\n", ret_val);  // Output the count of primes
}

// Cache-Friendly Sieve Implementation (Improves memory access pattern)
void sieve_friendly(int n){
    int ret_val = 0;
    bool* X = malloc(sizeof(bool) * n);  // Boolean array to store sieve status
    int root_N = (int) sqrt(n);  // Calculate the square root of n
    int factors[root_N];  // Array to store the primes up to sqrt(n)
    int factor_count = 0;

    // Initialize the array X to 1 (assume all numbers are prime)
    for(int i = 2; i < n; i++) {
        X[i] = 1;
    }

    double t = omp_get_wtime();  // Start the timer

    // Find primes up to sqrt(n) and store them in the factors array
    for(int i = 2; i <= root_N; i++) {
        if(X[i] == 0) {  // Skip non-prime numbers
            continue;
        }
        factors[factor_count++] = i;  // Store prime numbers
        // Mark multiples of i as non-prime (0)
        for(long j = 2 * i; j <= root_N; j += i) {
            X[j] = 0;
        }
    }

    // Sieve the range from root_N + 1 to n in chunks of size root_N
    for(int i = root_N + 1; i < n; i += root_N) {
        long start;
        long end = (i + root_N - 1 < n) ? (i + root_N - 1) : n;  // Calculate the end of the range

        // Mark multiples of primes found earlier in this chunk
        for(int j = 0; j < factor_count; j++) {
            int temp = factors[j];
            start = i;
            // Adjust the starting point if it's not a multiple of the prime
            if(start % temp != 0) {
                start = i + (temp - i % temp);
            }
            // Mark the multiples as non-prime
            for(; start < end; start += temp) {
                X[start] = 0;
            }
        }

        // Count primes in this chunk
        for(long start = i; start <= end; start++) {
            if(X[start] == 1) {  // If X[start] is 1, it's a prime
                ret_val++;
            }
        }
    }

    t = omp_get_wtime() - t;  // Stop the timer
    printf("Time taken (cache friendly): %.4f seconds\n", t);

    // Print the primes found (optional)
    // print_arr(X, n);
    
    free(X);  // Free the allocated memory
    ret_val += factor_count;  // Add the count of primes found up to sqrt(n)
    printf("Number of primes: %d\n", ret_val);  // Output the count of primes
}

// Parallelized Cache-Friendly Sieve Implementation (Using OpenMP for parallelism)
void sieve_parallel_friendly(int n){
    int ret_val = 0;
    bool* X = malloc(sizeof(bool) * n);  // Boolean array to store sieve status
    int root_N = (int) sqrt(n);  // Calculate the square root of n
    int factors[root_N];  // Array to store the primes up to sqrt(n)
    int factor_count = 0;

    // Initialize the array X to 1 (assume all numbers are prime)
    for(int i = 2; i < n; i++) {
        X[i] = 1;
    }

    double t = omp_get_wtime();  // Start the timer

    // Find primes up to sqrt(n) and store them in the factors array
    for(int i = 2; i <= root_N; i++) {
        if(X[i] == 0) {  // Skip non-prime numbers
            continue;
        }
        factors[factor_count++] = i;  // Store prime numbers
        // Mark multiples of i as non-prime (0)
        for(int j = 2 * i; j <= root_N; j += i) {
            X[j] = 0;
        }
    }

    // Parallelize the sieving process using OpenMP
    #pragma omp parallel for reduction(+:ret_val)
    for(long i = root_N + 1; i < n; i += root_N) {
        long start;
        long end = (i + root_N - 1 < n) ? (i + root_N - 1) : n;  // Calculate the end of the range
        
        // Mark multiples of primes found earlier in this chunk
        for(int j = 0; j < factor_count; j++) {
            int temp = factors[j];
            start = i;
            // Adjust the starting point if it's not a multiple of the prime
            if(start % temp != 0) {
                start = i + (temp - i % temp);
            }
            // Mark the multiples as non-prime
            for(; start < end; start += temp) {
                X[start] = 0;
            }
        }

        // Count primes in this chunk
        for(long start = i; start <= end; start++) {
            if(X[start] == 1) {  // If X[start] is 1, it's a prime
                ret_val++;
            }
        }
    }

    t = omp_get_wtime() - t;  // Stop the timer
    printf("Time taken (parallelized cache-friendly): %.4f seconds\n", t);

    // Print the primes found (optional)
    // print_arr(X, n);
    
    free(X);  // Free the allocated memory
    ret_val += factor_count;  // Add the count of primes found up to sqrt(n)
    printf("Number of primes: %d\n", ret_val);  // Output the count of primes
}

int main(int argc, char *argv[]){
    long n = atoi(argv[1]) + 1;  // Get the upper limit for sieve (and adjust for 0-based indexing)
    sieve_unfriendly(n);  // Call the sieve unfriendly to cache
    sieve_friendly(n);    // Call the cache-friendly sieve
    sieve_parallel_friendly(n);  // Call the parallelized cache-friendly sieve
    return 0;
}
