#!/bin/bash

arr_size=(100 1000 10000 100000 1000000)
threads=(1 2 4 8 16)

rm output.txt

printf "\t\t" >> output.txt
for i in "${arr_size[@]}"; do
    printf "$i\t\t" >> output.txt
done
printf "\n" >> output.txt

for i in "${threads[@]}"; do
    printf "%d\t\t" ${i} >> output.txt
    for j in "${arr_size[@]}"; do
        ./a.out ${i} ${j} >> output.txt
    done
    printf "\n" >> output.txt
done


cat output.txt
