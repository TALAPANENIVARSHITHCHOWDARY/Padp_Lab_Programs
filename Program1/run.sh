#!/bin/bash

# Define an array of problem sizes (number of iterations for the program)
arr_size=(100 1000 10000 100000 1000000)

# Define an array of thread counts (number of threads to be used in the program)
threads=(1 2 4 8 16)

# Remove the output file if it exists to start fresh
rm output.txt

# Add headers for the table in the output file
# The first row will contain the problem sizes (iterations)
printf "\t\t" >> output.txt  # Add initial empty space for alignment
for i in "${arr_size[@]}"; do
    printf "$i\t\t" >> output.txt  # Print problem sizes with spacing
done
printf "\n" >> output.txt  # Move to the next line after headers

# Loop through each thread count
for i in "${threads[@]}"; do
    # Write the current thread count at the start of the row
    printf "%d\t\t" ${i} >> output.txt

    # Loop through each problem size
    for j in "${arr_size[@]}"; do
        # Execute the compiled program (`a.out`) with current thread count and problem size
        # Append the output of the program to the output file
        ./a.out ${i} ${j} >> output.txt
    done

    # After all problem sizes are processed for this thread count, move to the next line
    printf "\n" >> output.txt
done

# Display the contents of the output file in the terminal
cat output.txt
