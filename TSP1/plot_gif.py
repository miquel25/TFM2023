import numpy as np
import matplotlib.pylab as plt
import matplotlib.animation as animation
import os
import pandas as pd
from celluloid import Camera

def plot_gif(name):
    N = len(os.listdir(name+'_gif'))

    df = pd.read_csv("results/random_graph.txt", delimiter='\t', skiprows=[0], header=None)

    fig, ax = plt.subplots()
    camera = Camera(fig)

    for n in range(N):
        ax.plot(df[0],df[1],'ko',ms=7)
        v = np.loadtxt(name+'_gif/'+str(n+1)+'.txt')
        j = v[0]
        for i in v:
            ax.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],'C0-',linewidth=2)
            j = i
        ax.plot(df[0][0],df[1][0],'ro',ms=8)
        ax.text(0,0,f"Iteration: {n}")
        camera.snap()
    plt.show()
    animation = camera.animate()
    try: animation.save('results/'+name+'.gif', writer='imagemagick')
    except: animation.save('results/'+name+'.mp4', writer='ffmpeg')
    


# plot_gif('NN')
# plot_gif('NI')
plot_gif('GA')