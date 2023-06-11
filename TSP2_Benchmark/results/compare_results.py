import numpy as np
import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')
plt.rc( 'font', size=14, family="DejaVu Sans" )
plt.rc( 'text', usetex=True)
import pandas as pd

def ustd(list):
    return np.var(list)/np.sqrt(len(list))

nn = np.loadtxt("BMK_NN.txt")
ni = np.loadtxt("BMK_NI.txt")

sa = pd.read_csv("BMK_SA.txt", sep=' ', header=None)
ga = pd.read_csv("BMK_GA.txt", sep=' ', header=None)
aco = pd.read_csv("BMK_ACO.txt", sep=' ', header=None)


realSolution = np.loadtxt("best_benchmark.txt")
graph = pd.read_csv("random_graph.txt",skiprows=1, header=None, sep='\t')

Freal = 0
for i in range(1,len(realSolution)):
    Freal+=np.sqrt((graph[0][realSolution[i]]-graph[0][realSolution[i-1]])**2+(graph[1][realSolution[i]]-graph[1][realSolution[i-1]])**2)


def hist(sa,ga,aco):
    plt.figure(dpi=200)
    bins=np.linspace(min(aco[0]),465,15)
    aco_heights, aco_bins = np.histogram(aco[0], bins=bins)
    ga_heights, ga_bins = np.histogram(ga[0], bins=aco_bins)
    sa_heights, sa_bins = np.histogram(sa[0], bins=ga_bins)
    
    width = (ga_bins[1] - ga_bins[0])/4

    plt.bar(aco_bins[:-1]-width, aco_heights, width=width, label='Ant Colony Optimization')
    plt.bar(ga_bins[:-1], ga_heights, width=width, label='Genetic Algorithm')
    plt.bar(sa_bins[:-1]+width, sa_heights, width=width, label='Simulated Annealing')
    
    plt.axvline(Freal,color='k',linestyle='--',label='Analytic solution')
    plt.axvline(nn[0],color='C3',linestyle='-',label='Nearest Neighbour',lw=4)
    plt.axvline(ni[0],color='C4',linestyle='-',label='Nearest Insertion', lw=4)
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5), fontsize=12)
    plt.xlabel("tour length (km)")
    plt.ylabel("frequency")
    plt.show()


def mean_plot(sa,ga,aco, nn ,ni):
    labels = ['Ant Colony Optimization','Genetic Algorithm','Simulated Annealing']
    mean = [np.mean(aco), np.mean(ga),np.mean(sa)]
    umean = [ustd(aco), ustd(ga),ustd(sa)]

    fig, (ax2, ax1) = plt.subplots(2,1,sharex=True,dpi=200)
    # fig, ax1 = plt.subplots(dpi=200)
    ax1.plot(['Nearest Neighbour','Nearest Insertion'],[nn,ni],'o',ms=3)
    ax1.errorbar(labels,mean,yerr=umean,fmt='.', elinewidth=0.5, capsize=2, color='C0')
    ax2.plot(['Nearest Neighbour','Nearest Insertion'],[nn,ni],'o',ms=3)
    ax2.errorbar(labels,mean,yerr=umean,fmt='.', elinewidth=0.5, capsize=2, color='C0')
    # ax1.set_ylim(-0.005,0.075)
    # ax2.set_ylim(1.695,1.775)
    ax1.set_ylim(418.5,426.5)
    ax2.set_ylim(458.5,466.5)
    plt.xticks(rotation=-45, ha='left')
    fig.text(0.0, 0.5, "tour length (km)", va='center', rotation='vertical')
    # fig.text(0.0, 0.5, "computation time (s)", va='center', rotation='vertical')


    ax1.spines['top'].set_linestyle((0,(5,5)))
    ax2.spines['bottom'].set_linestyle((0,(5,5)))
    d = .015  # how big to make the diagonal lines in axes coordinates
    # arguments to pass to plot, just so we don't keep repeating them
    kwargs = dict(transform=ax2.transAxes, color='lightgrey', lw=1, clip_on=False)
    ax2.plot((-d, +d), (-d, +d), **kwargs)        # top-left diagonal
    ax2.plot((1 - d, 1 + d), (-d, +d), **kwargs)  # top-right diagonal

    kwargs.update(transform=ax1.transAxes)  # switch to the bottom axes
    ax1.plot((-d, +d), (1 - d, 1 + d), **kwargs)  # bottom-left diagonal
    ax1.plot((1 - d, 1 + d), (1 - d, 1 + d), **kwargs)  # bottom-right diagonal
    plt.show()

hist(sa,ga,aco)
mean_plot(sa[0],ga[0],aco[0],nn[0],ni[0])
# mean_plot(sa[1],ga[1],aco[1],nn[1],ni[1])


# plt.hist(aco[0],bins=25)
# plt.show()
# plt.hist(ga[0],bins=25)
# plt.show()
# plt.hist(sa[0],bins=25)
# plt.show()