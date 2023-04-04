import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def acc(i,j):
    if i<j:
        return int((i*(i-1))/2+j)
    else:
        return int((j*(j-1))/2+i)

def antpath(root,p,N):
    P = [root]
    v = [0]*N
    v[root] = 1
    for i in range(1,N):
        sum = 0
        for j in range(N):
            if v[j]==0:
                sum+=p[acc(P[-1],j)]
        new = np.random.uniform(low=0,high=sum)
        sum = 0
        for j in range(N):
            if v[j]==0:
                sum+=p[acc(P[-1],j)]
            if sum>new:
                new = j
                break
        P.append(new)
        v[new]=1
    P.append(root)
    return P

def d(x1,y1,x2,y2):
    return ((x1-x2)**2+(y1-y2)**2)**(1/2)

def Fitness(P,nodes):
    dist = 0
    for i in range(1,len(P)-1):
        dist += d(nodes['x'][P[i-1]],nodes['y'][P[i-1]],nodes['x'][P[i]],nodes['y'][P[i]])
    return dist

def ACO(nodes):
    N = nodes.shape[0]
    n = int(N*(N-1)/2)

    e = 0.3
    popsize = 3
    gamma = 1

    p = [gamma]*n
    best = []
    m = 5000
    k=0
    while(k<10000):
        P = []
        for i in range(popsize):
            root = np.random.randint(0,N-1)
            P.append(antpath(root,p,N))
            if m>Fitness(P[-1],nodes):
                m = Fitness(P[-1],nodes)
                best = P[-1]
                print(f"{m:.0f}",best)
        for i in range(n):
            p[i]=(1-e)*p[i]
        for i in range(len(P)):
            F = 1/Fitness(P[i],nodes)
            for j in range(len(P[i])):
                p[acc(P[i][j-1],P[i][j])]=p[acc(P[i][j-1],P[i][j])]+F
        k+=1
       
        
        

nodes = pd.read_csv("results/random_graph.txt", delimiter='\t', skiprows=[0], header=None)
nodes = nodes.rename(columns={0:'x',1:'y'})

ACO(nodes)