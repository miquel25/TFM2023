import numpy as np
import matplotlib.pyplot as plt
# plt.style.use('seaborn-whitegrid')
import pandas as pd

nn = np.loadtxt("BMK_NN.txt")
ni = np.loadtxt("BMK_NI.txt")

sa = pd.read_csv("BMK_SA.txt", sep=' ', header=None)
ga = pd.read_csv("BMK_GA.txt", sep=' ', header=None)
aco = pd.read_csv("BMK_GA.txt", sep=' ', header=None)


realSolution = np.loadtxt("best_benchmark.txt")
graph = pd.read_csv("random_graph.txt",skiprows=1, header=None, sep='\t')

Freal = 0
for i in range(1,len(realSolution)):
    Freal+=np.sqrt((graph[0][realSolution[i]]-graph[0][realSolution[i-1]])**2+(graph[1][realSolution[i]]-graph[1][realSolution[i-1]])**2)


def hist(sa,ga,aco):
    ga_heights, ga_bins = np.histogram(ga[0])
    sa_heights, sa_bins = np.histogram(sa[0], bins=ga_bins)
    aco_heights, aco_bins = np.histogram(aco[0], bins=ga_bins)
    width = (ga_bins[1] - ga_bins[0])/4

    plt.bar(aco_bins[:-1]-width, aco_heights, width=width, label='Ant Colony Optimization')
    plt.bar(ga_bins[:-1], ga_heights, width=width, label='Genetic Algorithm')
    plt.bar(sa_bins[:-1]+width, sa_heights, width=width, label='Simulated Annealing')
    
    plt.axvline(Freal,color='r',linestyle='--',label='Analytic solution')
    plt.legend()
    plt.show()


def mean_plot(sa,ga,aco):
    labels = ['Ant Colony Optimization','Genetic Algorithm','Simulated Anneling']
    mean = [np.mean(aco[0]), np.mean(ga[0]),np.mean(sa[0])]
    umean = [np.var(aco[0]), np.var(ga[0]),np.var(sa[0])]
    
    plt.plot(['Nearest Neighbour','Nearest Insertion'],[nn[0],ni[0]],'o',ms=3)
    plt.errorbar(labels,mean,yerr=umean,fmt='.', capsize=5, color='C0')
    plt.xticks(rotation=-30, ha='left')
    plt.axhline(Freal,linestyle='--',color='r')

# hist(sa,ga,aco)
mean_plot(sa,ga,aco)