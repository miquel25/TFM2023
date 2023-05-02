import numpy as np
import matplotlib.pyplot as plt

l = np.loadtxt("SAlvst.txt")
m = np.loadtxt("SAmvst.txt")

plt.plot(l)
plt.plot(m)