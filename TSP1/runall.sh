gcc generate_graph.c -o generate_graph
gcc nearest_neighbour.c -o nearest_neighbour -lm
gcc nearest_insertion.c -o nearest_insertion -lm
gcc ACO.c -o ACO -lm
gcc GA.c -o GA -lm
gcc SA.c -o SA -lm
./generate_graph 25
./nearest_neighbour
./nearest_insertion
./ACO 10000
./GA 100000
./SA 100000
python3 plot_graph.py