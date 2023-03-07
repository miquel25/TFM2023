gcc generate_graph.c -o generate_graph
gcc nearest_neighbour.c -o nearest_neighbour -lm
gcc nearest_insertion.c -o nearest_insertion -lm
./generate_graph
./nearest_neighbour
./nearest_insertion
python3 plot_graph.py