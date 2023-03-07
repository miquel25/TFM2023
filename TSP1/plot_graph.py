import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def plot_path(name, color):
    v = np.loadtxt(name)

    df = pd.read_csv("random_graph.txt", delimiter='\t', skiprows=[0], header=None)

    plt.plot(df[0],df[1],'ko',ms=7)

    j = v[0]
    for i in v:
        plt.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],color+'-',linewidth=2)
        j = i
    plt.plot(df[0][0],df[1][0],'ro',ms=8)

plot_path("TSP_NN.txt",'C0')
plot_path("TSP_NI.txt",'C1')

plt.show()