import numpy as np
import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')
import pandas as pd

sa = pd.read_csv("BMK_SA.txt", sep=' ', header=None)
ga = pd.read_csv("BMK_GA.txt", sep=' ', header=None)

realSolution = np.loadtxt("best_benchmark.txt")
graph = pd.read_csv("random_graph.txt",skiprows=1, header=None, sep='\t')

Freal = 0
for i in range(1,len(realSolution)):
    Freal+=np.sqrt((graph[0][realSolution[i]]-graph[0][realSolution[i-1]])**2+(graph[1][realSolution[i]]-graph[1][realSolution[i-1]])**2)




def hist(sa,ga):
    fig, (ax0, ax1) = plt.subplots(1,2)
    # fig, ax1 = plt.subplots()
    ga_heights, ga_bins = np.histogram(ga[0])
    sa_heights, sa_bins = np.histogram(sa[0], bins=ga_bins)

    width = (ga_bins[1] - ga_bins[0])/3

    ax0.bar(sa_bins[:-1], sa_heights, width=width)
    ax0.bar(ga_bins[:-1]+width, ga_heights, width=width)
    ax0.axvline(Freal,color='r',linestyle='--')

    ax1.hist(sa[1],bins=2)
    ax1.hist(ga[1],bins=30)
    plt.show()

def mean_plot(sa,ga):
    labels = ['Simulated Anneling','Genetic Algorithm']
    mean = [np.mean(sa[0]), np.mean(ga[0])]
    umean = [np.var(sa[0]), np.var(ga[0])]
    
    plt.errorbar(labels,mean,yerr=umean,fmt='.', capsize=5)
    plt.axhline(Freal,linestyle='--',color='r')
    plt.show()

hist(sa,ga)
mean_plot(sa,ga)