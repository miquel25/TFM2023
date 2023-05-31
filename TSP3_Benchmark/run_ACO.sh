#!/bin/bash
rm results/BMK_ACO.txt
gcc ACO.c -o ACO -lm
for i in {1..10000}
do
    echo "Execution nº$i"
    ./ACO 10000 162 500
done