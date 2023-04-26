import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def plot_path(name, color):
    v = np.loadtxt('results/TSP_'+name+'.txt')

    df = pd.read_csv("results/random_graph.txt", delimiter='\t', skiprows=[0], header=None)

    plt.plot(df[0],df[1],'ko',ms=7)

    j = v[0]
    for i in v:
        plt.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],color+'-',linewidth=2)
        j = i
    plt.plot(df[0][0],df[1][0],'ro',ms=8)
    plt.show()

# plot_path("NN",'C0')
# plot_path("NI",'C1')
# plot_path("ACO", 'C2')
plot_path("GA", 'C3')