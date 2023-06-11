import numpy as np
import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')
plt.rc( 'font', size=14, family="DejaVu Sans" )
plt.rc( 'text', usetex=True)
import pandas as pd

def ustd(list):
    return np.std(list)/np.sqrt(len(list))

N = np.arange(10,100,10)
dlist = np.arange(2,10,2)

def discrepance(N,dlist):
    nn = []
    unn = []
    ni = []
    uni = []
    aco = []
    uaco = []
    ga = []
    uga = []
    sa = []
    usa = []

    for n in N:
        nntemp = []
        nitemp = []
        acotemp = []
        gatemp = []
        satemp = []

        for d in dlist:
            dmin = []
            dmin.append(np.loadtxt(f"NN/NN_{n}-{d}.txt")[0])
            dmin.append(np.loadtxt(f"NI/NI_{n}-{d}.txt")[0])
            dmin.append(min(np.loadtxt(f"ACO/ACO_{n}-{d}.txt")[:,0]))
            dmin.append(min(np.loadtxt(f"GA/GA_{n}-{d}.txt")[:,0]))
            dmin.append(min(np.loadtxt(f"SA/SA_{n}-{d}.txt")[:,0]))
            dmin = min(dmin)
            nntemp.append((np.loadtxt(f"NN/NN_{n}-{d}.txt")[0]-dmin)/dmin*100)
            nitemp.append((np.loadtxt(f"NI/NI_{n}-{d}.txt")[0]-dmin)/dmin*100)
            acotemp.append((np.mean(np.loadtxt(f"ACO/ACO_{n}-{d}.txt")[:,0])-dmin)/dmin*100)
            gatemp.append((np.mean(np.loadtxt(f"GA/GA_{n}-{d}.txt")[:,0])-dmin)/dmin*100)
            satemp.append((np.mean(np.loadtxt(f"SA/SA_{n}-{d}.txt")[:,0])-dmin)/dmin*100)
        nn.append(np.mean(nntemp))
        unn.append(ustd(nntemp))
        ni.append(np.mean(nitemp))
        uni.append(ustd(nitemp))
        aco.append(np.mean(acotemp))
        uaco.append(ustd(acotemp))
        ga.append(np.mean(gatemp))
        uga.append(ustd(gatemp))
        sa.append(np.mean(satemp))
        usa.append(ustd(satemp))

    plt.figure(dpi=200)
    plt.errorbar(N,nn,yerr=unn,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C3', label='Nearest Neighbour')
    plt.errorbar(N,ni,yerr=uni,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C4', label='Nearest Insertion')
    plt.errorbar(N,aco,yerr=uaco,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C0', label='Ant Colony Optimization')
    plt.errorbar(N,ga,yerr=uga,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C1', label='Genetic Algorithm')
    plt.errorbar(N,sa,yerr=usa,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C2', label='Simulated Annealing')
    plt.xlabel("$N$")
    plt.ylabel("Discrepance ($\%$)")
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5), fontsize=12)
    plt.show()

def time(N,dlist):
    nn = []
    unn = []
    ni = []
    uni = []
    aco = []
    uaco = []
    ga = []
    uga = []
    sa = []
    usa = []

    for n in N:
        nntemp = []
        nitemp = []
        acotemp = []
        gatemp = []
        satemp = []

        for d in dlist:
            nntemp.append(np.loadtxt(f"NN/NN_{n}-{d}.txt")[1])
            nitemp.append(np.loadtxt(f"NI/NI_{n}-{d}.txt")[1])
            acotemp.append(np.mean(np.loadtxt(f"ACO/ACO_{n}-{d}.txt")[:,1]))
            gatemp.append(np.mean(np.loadtxt(f"GA/GA_{n}-{d}.txt")[:,1]))
            satemp.append(np.mean(np.loadtxt(f"SA/SA_{n}-{d}.txt")[:,1]))
        nn.append(np.mean(nntemp))
        unn.append(ustd(nntemp))
        ni.append(np.mean(nitemp))
        uni.append(ustd(nitemp))
        aco.append(np.mean(acotemp))
        uaco.append(ustd(acotemp))
        ga.append(np.mean(gatemp))
        uga.append(ustd(gatemp))
        sa.append(np.mean(satemp))
        usa.append(ustd(satemp))

    plt.figure(dpi=200)
    plt.errorbar(N,nn,yerr=unn,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C3', label='Nearest Neighbour')
    plt.errorbar(N,ni,yerr=uni,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C4', label='Nearest Insertion')
    plt.errorbar(N,aco,yerr=uaco,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C0', label='Ant Colony Optimization')
    plt.errorbar(N,ga,yerr=uga,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C1', label='Genetic Algorithm')
    plt.errorbar(N,sa,yerr=usa,fmt='-',ms=3,capsize=2, elinewidth=0.5, color='C2', label='Simulated Annealing')
    plt.xlabel("$N$")
    plt.ylabel("Computation time (s)")
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5), fontsize=12)
    plt.show()

discrepance(N,dlist)
time(N,dlist)