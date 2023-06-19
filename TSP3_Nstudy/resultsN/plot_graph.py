import numpy as np
import matplotlib.pyplot as plt
plt.rc( 'font', size=18, family="DejaVu Sans" )
plt.rc( 'text', usetex=True)
import pandas as pd
import os
# plt.figure(dpi=200)

def plot_path(name, color, graph='10-2'):
    # plt.figure(dpi=200)
    v = np.loadtxt(name+'/'+name+'_'+graph+'.txt')

    df = pd.read_csv("graph/random_graph_"+graph+".txt", delimiter='\t', skiprows=[0], header=None)

    j= v[0]
    for i in v:
        plt.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],color+'-',linewidth=2,alpha=0.5)
        j = i

    plt.plot(df[0],df[1],'ko',ms=5)
    plt.plot(df[0][0],df[1][0],'ro',ms=5)

    plt.xlabel("$x$ (km)")
    plt.ylabel("$y$ (km)")
    # plt.show()

def plot_Ngraph(name,color):
    graph = ['10-2','20-6','30-4', '40-10', '50-8','60-4','70-2','80-8','90-6','100-10']
    for g in graph:
        plt.figure(dpi=200)
        plot_path(name,color,g)
        directory = "plots/"+g+"/"
        if not os.path.exists(directory):
            os.makedirs(directory)
        plt.savefig("plots/"+g+"/"+name+"_"+g+".png")
        plt.show()

plot_Ngraph("NN",'C4')
plot_Ngraph("NI",'C5')
plot_Ngraph("ACO", 'C0')
plot_Ngraph("GA", 'C1')
plot_Ngraph("SA",'C2')

# plt.show()