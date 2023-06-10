import numpy as np
import matplotlib.pyplot as plt
plt.rc( 'font', size=18, family="DejaVu Sans" )
plt.rc( 'text', usetex=True)
import pandas as pd

def plot_path(name, color):
    plt.figure(dpi=200)
    v = np.loadtxt('results/BMK_'+name+'.txt')

    df = pd.read_csv("results/random_graph.txt", delimiter='\t', skiprows=[0], header=None)

    j= v[0]
    for i in v:
        plt.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],color+'-',linewidth=2)
        j = i

    plt.plot(df[0],df[1],'ko',ms=12)
    plt.plot(df[0][0],df[1][0],'ro',ms=12)
    for i in range(df.shape[0]):
        plt.text(df[0][i],df[1][i],str(i),color='white',fontsize=14, ha='center', va='center')

    plt.xlabel("$x$ (km)")
    plt.ylabel("$y$ (km)")
    plt.show()

# plot_path("NN",'C4')
# plot_path("NI",'C5')
plot_path("ACO", 'C0')
plot_path("GA", 'C1')
plot_path("SA",'C2')