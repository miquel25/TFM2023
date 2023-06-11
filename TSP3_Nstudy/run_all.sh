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
gcc cluster_parameters_ACO.c -o cluster_parameters_ACO -lm
gcc cluster_parameters_GA.c -o cluster_parameters_GA -lm
gcc cluster_parameters_SA.c -o cluster_parameters_SA -lm

echo "RUN AS ./run_all.sh var1 var2 var3"
echo "var1 = Nmin"
echo "var2 = Nmax"
echo "var3 = Nstep"
Niter=50

for ((i=$1; i<=$2; i=i+$3)); do
    echo "N = $i"

    for ((j=2; j<=10; j=j+2)); do
        ./generate_graph $i $j
        taskset -c 0 ./nearest_neighbour "graph/random_graph_$i-$j.txt" "results/NN/NN_$i-$j.txt"
        taskset -c 0 ./nearest_insertion "graph/random_graph_$i-$j.txt" "results/NI/NI_$i-$j.txt"

        taskset -c 0-31 ./cluster_parameters_ACO "graph/random_graph_$i-$j.txt" "-"
        filename="parameters/ACO-best.txt"
        n=1
        while read -r line;do
            if (($n == 1)); then
                param1=$line
            fi
            if ((n==1)); then
                param1=$line
            fi
            n=$((n+1))
        done < $filename
        for k in {0..31}; do
            taskset -c $k ./ACO "graph/random_graph_$i-$j.txt" "results/ACO/ACO_$i-$j.txt" 1000 $param1 $param2 &
        done
        wait

        taskset -c 0-31 ./cluster_parameters_GA "graph/random_graph_$i-$j.txt" "-"
        filename="parameters/GA-best.txt"
        n=1
        while read -r line;do
            if (($n == 1)); then
                param1=$line
            fi
            if ((n==1)); then
                param1=$line
            fi
            n=$((n+1))
        done < $filename
        for k in {0..31}; do
            taskset -c $k ./GA "graph/random_graph_$i-$j.txt" "results/GA/GA_$i-$j.txt" 10000 $param1 $param2 &
        done
        wait

        taskset -c 0-31 ./cluster_parameters_SA "graph/random_graph_$i-$j.txt" "-"
        filename="parameters/SA-best.txt"
        n=1
        while read -r line;do
            if (($n == 1)); then
                param1=$line
            fi
            if ((n==1)); then
                param1=$line
            fi
            n=$((n+1))
        done < $filename
        for k in {0..31}; do
            taskset -c $k ./SA "graph/random_graph_$i-$j.txt" "results/SA/SA_$i-$j.txt" $param1 $param2 &
        done
    done
done
wait
