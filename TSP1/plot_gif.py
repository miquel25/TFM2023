import numpy as np
import matplotlib.pylab as plt
import os
import pandas as pd
from celluloid import Camera
from IPython.display import HTML

N = len(os.listdir('NI_gif'))

df = pd.read_csv("random_graph.txt", delimiter='\t', skiprows=[0], header=None)

fig, ax = plt.subplots()
camera = Camera(fig)

for n in range(N):
    ax.plot(df[0],df[1],'ko',ms=7)
    v = np.loadtxt('NI_gif/'+str(n+1)+'.txt')
    j = v[0]
    for i in v:
        ax.plot([df[0][j],df[0][i]],[df[1][j],df[1][i]],'C0-',linewidth=2)
        j = i
    ax.plot(df[0][0],df[1][0],'ro',ms=8)
    camera.snap()
    

animation = camera.animate()
HTML(animation.to_html5_video())