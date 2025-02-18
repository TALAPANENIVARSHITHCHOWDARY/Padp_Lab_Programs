#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <omp.h>

#define COUNT 7
#define MAX_SIZE 20

// File name to be processed
char *file_name;

// Words to search for in the file
char words[COUNT][MAX_SIZE] = {"Hi", "Hello", "How", "Are", "You", "Doing", "Today"};

// Array to store the count of each word
int word_count[COUNT] = {0};

// Function to read a single word from the file
void read_word(char *temp, FILE *fp) {
    int i = 0;
    char ch;

    // Skip non-alphabet characters
    while ((ch = fgetc(fp)) != EOF && isalpha(ch) == 0);

    // Read the word
    while (ch != EOF && isalpha(ch)) {
        temp[i++] = ch;
        ch = fgetc(fp);
    }
    temp[i] = '\0'; // Null-terminate the word
}

// Function to count occurrences of a specific word in the file
int get_word_count(int num) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", file_name);
        exit(1);
    }

    char temp[MAX_SIZE]; // Buffer to store words from the file
    int ret_val = 0;

    // Read words from the file and count matches
    while (!feof(fp)) {
        read_word(temp, fp);
        if (strcasecmp(temp, words[num]) == 0) { // Case-insensitive comparison
            ret_val++;
        }
    }

    fclose(fp); // Close the file to avoid resource leaks
    return ret_val;
}

int main(int argc, char *argv[]) {
    // Validate command-line arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file_name> <num_threads>\n", argv[0]);
        return 1;
    }

    file_name = argv[1];
    int tnum = atoi(argv[2]); // Number of threads

    double t = omp_get_wtime(); // Start timing

    // Parallel region to count word occurrences
    #pragma omp parallel for num_threads(tnum)
    for (int i = 0; i < COUNT; i++) {
        word_count[i] = get_word_count(i);
    }

    // Print the results
    for (int i = 0; i < COUNT; i++) {
        printf("%s: %d\n", words[i], word_count[i]);
    }

    printf("Time taken: %lf seconds\n", omp_get_wtime() - t); // Print execution time
    return 0;
}
