#!/bin/bash
rm results/BMK_SA.txt
gcc SA.c -o SA  -lm
for i in {1..300}; do
    echo "Execution nº$(($(($i-1))*32+1))-$(($i*32-1))"
    for k in {0..31}; do
        taskset -c $k ./SA 600 0.7 &
    done
    wait
done