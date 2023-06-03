#!/bin/bash
rm results/BMK_SA.txt
for i in {1..10000}
do
    echo "Execution nº$i"
    ./SA
done