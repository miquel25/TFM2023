import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("results/BMK_GA.txt", header=None, sep=' ')

ax1 = plt.axes()
ax1.hist(df[0], bins=15, label='Fitness')
ax2 = ax1.twiny()
ax2.hist(df[1], bins=15, label='time(s)', color='C1')
plt.show()