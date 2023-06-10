#!/bin/bash
rm results/BMK_GA.txt
gcc GA.c -o GA -lm
for i in {1..300}; do
    echo "Execution nº$(($(($i-1))*32+1))-$(($i*32-1))"
    for k in {0..31}; do
        taskset -c $k ./GA results/random_graph.txt results/BMK_GA.txt 500 10 0.8 &
    done
    wait
done