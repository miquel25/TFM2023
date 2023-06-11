#!/bin/bash

gcc cluster_parameters_ACO.c -o cluster_parameters_ACO -lm
gcc cluster_parameters_GA.c -o cluster_parameters_GA -lm
gcc cluster_parameters_SA.c -o cluster_parameters_SA -lm
./cluster_parameters_ACO results/random_graph.txt -
./cluster_parameters_GA results/random_graph.txt -
./cluster_parameters_SA results/random_graph.txt -