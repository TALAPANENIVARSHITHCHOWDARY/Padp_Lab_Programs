#!/bin/bash

# Declare an associative array to map file sizes (keys) to corresponding file names (values)
declare -A my_files
my_files["1.25"]="Passage_1MB.txt"  # File size 1.25 MB mapped to Passage_1MB.txt
my_files["2.5"]="Passage_2MB.txt"   # File size 2.5 MB mapped to Passage_2MB.txt
my_files["5"]="Passage_5MB.txt"     # File size 5 MB mapped to Passage_5MB.txt
my_files["10"]="Passage_10MB.txt"   # File size 10 MB mapped to Passage_10MB.txt

# Define file size keys and thread counts for benchmarking
keys=("1.25" "2.5" "5" "10")        # Array of file sizes (in MB) to test
num_threads=(1 2 4 8)               # Array of thread counts to test with the program

# Remove the output file if it already exists to ensure a fresh start
rm output.txt

# Print the header row of the output file, indicating thread counts
printf "\t" >> output.txt           # Print a tab as the first column header
for tnum in "${num_threads[@]}"; do # Loop through each thread count
    printf "%d\t" ${tnum} >> output.txt  # Add thread count as a column header
done
printf "\n" >> output.txt           # Move to the next line after printing all thread counts

# Run the benchmark for each file size and thread count
for key in "${keys[@]}"; do         # Outer loop: iterate through each file size key
    printf "%s\t" ${key} >> output.txt  # Add the file size (key) as the first column of the row
    for tnum in "${num_threads[@]}"; do # Inner loop: iterate through each thread count
        # Run the C program (a.out) with the current file and thread count, append result to output.txt
        ./a.out ${my_files[$key]} ${tnum} >> output.txt
    done
    printf "\n" >> output.txt       # Move to the next line after processing all thread counts for the file size
done

# Display the contents of the output file in the terminal
cat output.txt
