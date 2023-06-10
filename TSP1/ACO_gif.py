import numpy as np
import matplotlib.pylab as plt
import matplotlib.animation as animation
import os
import pandas as pd
from celluloid import Camera

def plot_gif(name='ACO'):

    N = len(os.listdir(name+'_gif'))

    df = pd.read_csv("results/random_graph.txt", delimiter='\t', skiprows=[0], header=None)

    fig, ax = plt.subplots()
    camera = Camera(fig)

    for n in np.arange(0,N*100,100):
        p = pd.read_csv(name+'_gif/'+str(n)+'.txt', delimiter='\t', header=None)
        p[2] = p[2]/max(p[2])
        for i in range(p.shape[0]):
            ax.plot([df[0][p[0][i]],df[0][p[1][i]]],[df[1][p[0][i]],df[1][p[1][i]]],'C0-',linewidth=2, alpha=p[2][i])
            j = i
        ax.plot(df[0],df[1],'ko',ms=7)
        ax.text(0,0,f"Iteration: {n}")
        camera.snap()
    plt.show()
    animation = camera.animate()
    try: animation.save('results/'+name+'.gif', writer='imagemagick')
    except: animation.save('results/'+name+'.mp4', writer='ffmpeg')
    
plot_gif()
