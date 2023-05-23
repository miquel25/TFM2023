import numpy as np
import matplotlib.pyplot as plt

l = np.loadtxt("SAlvst.txt")
m = np.loadtxt("SAmvst.txt")

fig, ax1 = plt.subplots()
ax2 = plt.twinx()
ax1.plot(l)
ax2.plot(m, 'C1')
plt.show()