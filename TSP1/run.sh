gcc nearest_neighbour.c -o nearest_neighbour -lm
gcc nearest_insertion.c -o nearest_insertion -lm
./nearest_neighbour
./nearest_insertion
python3 plot_graph.py