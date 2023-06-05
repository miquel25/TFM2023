#!/bin/bash
proc=48
jobs="\j"

rm -r graph
mkdir graph

rm -r results/NN
rm -r results/NI
rm -r results/ACO
rm -r results/GA
rm -r results/SA

mkdir results/NN
mkdir results/NI
mkdir results/ACO
mkdir results/GA
mkdir results/SA

gcc generate_graph.c -o generate_graph -lm
gcc nearest_neighbour.c -o nearest_neighbour -lm
gcc nearest_insertion.c -o nearest_insertion -lm
gcc ACO.c -o ACO -lm
gcc GA.c -o GA -lm
gcc SA.c -o SA -lm

echo "RUN AS ./run_all.sh var1 var2 var3"
echo "var1 = Nmin"
echo "var2 = Nmax"
echo "var3 = Nstep"
Niter=50

for ((i=$1; i<=$2; i=i+$3)); do
    echo "N = $i"

    for ((j=2; j<=10; j=j+2)); do
        ./generate_graph $i $j
        ./nearest_neighbour "graph/random_graph_$i-$j.txt" "results/NN/NN_$i-$j.txt"
        ./nearest_insertion "graph/random_graph_$i-$j.txt" "results/NI/NI_$i-$j.txt"
        for k in {1..50}; do
            ((k=k%proc)); ((k++==0)) && wait
            ./ACO "graph/random_graph_$i-$j.txt" "results/ACO/ACO_$i-$j.txt" &
        done
        wait
        for k in {1..50}; do
            ((k=k%proc)); ((k++==0)) && wait
            ./GA "graph/random_graph_$i-$j.txt" "results/GA/GA_$i-$j.txt" &
        done
        wait
        for k in {1..50}; do
            ((k=k%proc)); ((k++==0)) && wait
            ./SA "graph/random_graph_$i-$j.txt" "results/SA/SA_$i-$j.txt" &
        done
    done
done
wait
