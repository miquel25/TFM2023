import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import itertools

def d(x1,y1,x2,y2):
    return np.sqrt((x1-x2)**2+(y1-y2)**2)


df = pd.read_csv("random_graph.txt", delimiter='\t', skiprows=[0], header=None)
N = df.shape[0]-1

F = [0]*np.math.factorial(N)

i = 0
P = list(itertools.permutations(range(1,N+1)))
for v in itertools.permutations(range(1,N+1)):
    previous = 0
    for j in v:
        F[i]+=d(df[0][previous],df[1][previous],df[0][j],df[1][j])
        previous = j
    F[i]+=d(df[0][previous],df[1][previous],df[0][0],df[1][0])
    i+=1

a1, a2, a3 = plt.hist(F, bins=30)
print(a1)
print(a2)

mn = min(F)
m = []
for i in range(len(F)):
    if F[i]==mn:
        m.append(i)

for i in range(len(m)):
    best = list(P[m[i]])
    best.insert(0,0)
    best.append(0)
    print(best)
    print(f"Total distance {min(F):.2f}")
    np.savetxt('best'+str(i)+'_benchmark.txt',best,fmt="%d")