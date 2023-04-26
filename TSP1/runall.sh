gcc generate_graph.c -o generate_graph
gcc nearest_neighbour.c -o nearest_neighbour -lm
gcc nearest_insertion.c -o nearest_insertion -lm
gcc ACO.c -o ACO -lm
gcc GA.c -o GA -lm
./generate_graph 10
./nearest_neighbour
./nearest_insertion
./ACO
./GA
python3 plot_graph.py