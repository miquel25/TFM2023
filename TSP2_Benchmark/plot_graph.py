import numpy as np
import matplotlib.pyplot as plt
plt.rc( 'font', size=18, family="DejaVu Sans" )
plt.rc( 'text', usetex=True)
import pandas as pd

plt.figure(dpi=200)

def plot_path(name, color):
    # v = np.loadtxt('results/TSP_'+name+'.txt')

    df = pd.read_csv("results/random_graph.txt", delimiter='\t', skiprows=[0], header=None)

    plt.plot(df[0],df[1],'ko',ms=7)

    # for i in v:
    #     plt.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],color+'-',linewidth=2)
    #     j = i
    plt.plot(df[0][0],df[1][0],'ro',ms=8)
    plt.xlabel("$x$ (km)")
    plt.ylabel("$y$ (km)")
    plt.show()

plot_path("NN",'C0')
# plot_path("NI",'C1')
# plot_path("ACO", 'C2')
# plot_path("GA", 'C3')
# plot_path("SA",'C4')