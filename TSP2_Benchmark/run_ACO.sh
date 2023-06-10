#!/bin/bash
rm results/BMK_ACO.txt
gcc ACO.c -o ACO -lm
for i in {1..300}; do
    echo "Execution nº$(($(($i-1))*32+1))-$(($i*32-1))"
    for k in {0..31}; do
        taskset -c $k ./ACO results/random_graph.txt results/BMK_ACO.txt 1500 162 500 &
    done
    wait
done