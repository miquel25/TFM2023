#!/bin/bash
rm results/BMK_GA.txt
for i in {1..1000}
do
    echo "Execution nº$i"
    ./GA
done