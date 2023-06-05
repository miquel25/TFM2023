import numpy as np
import matplotlib.pyplot as plt
# plt.style.use('seaborn-whitegrid')
import pandas as pd

N = np.arange(10,100,50)
dmin = np.arange(2,10,2)

nn = []
ni = []
aco = []
uaco = []
minaco = []
ga = []
uga = []
minga = []
sa = []
usa = []
minsa = []

n = 100
for d in dmin:
    nn.append(np.loadtxt(f"NN/NN_{n}-2.txt")[0])
    ni.append(np.loadtxt(f"NI/NI_{n}-2.txt")[0])
    aco.append(np.mean(np.loadtxt(f"ACO/ACO_{n}-{d}.txt")[:,0]))
    uaco.append(np.mean(np.loadtxt(f"ACO/ACO_{n}-{d}.txt")[:,0]))
    minaco.append(min(np.loadtxt(f"ACO/ACO_{n}-{d}.txt")[:,0]))
    ga.append(np.mean(np.loadtxt(f"GA/GA_{n}-{d}.txt")[:,0]))
    uga.append(np.mean(np.loadtxt(f"GA/GA_{n}-{d}.txt")[:,0]))
    minga.append(min(np.loadtxt(f"GA/GA_{n}-{d}.txt")[:,0]))
    sa.append(np.mean(np.loadtxt(f"SA/SA_{n}-{d}.txt")[:,0]))
    usa.append(np.mean(np.loadtxt(f"SA/SA_{n}-{d}.txt")[:,0]))
    minsa.append(min(np.loadtxt(f"SA/SA_{n}-{d}.txt")[:,0]))

x = dmin

plt.errorbar(x,nn,fmt='o',ms=3)
plt.errorbar(x,ni,fmt='o',ms=3)
plt.errorbar(x,aco,yerr=uaco,fmt='o',ms=3,capsize=3)
plt.errorbar(x,ga,yerr=uga,fmt='o',ms=3,capsize=3)
plt.errorbar(x,sa,yerr=usa,fmt='o',ms=3,capsize=3)
plt.show()

plt.plot(x,nn,'o')
plt.plot(x,ni,'o')
plt.plot(x,minaco,'o')
plt.plot(x,minga,'o')
plt.plot(x,minsa,'o')
plt.show()