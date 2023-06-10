import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv("ACO_params.txt", sep=' ')
pop = df.sort_values('popsize')['popsize'].unique().tolist()
gam = df.sort_values('gamma')['gamma'].unique().tolist()
F = np.zeros([len(pop),len(gam)])

for i in range(len(pop)):
    for j in range(len(gam)):
        F[i][j] = df[(df['popsize']==pop[i]) & (df['gamma']==gam[j])]['Fitness'].tolist()[0]

plt.pcolormesh(gam,pop,F)
plt.xlabel("gamma")
plt.ylabel("popsize")
plt.colorbar()
plt.show()

# plt.plot(gam,df[df['popsize']==190]['Fitness'])
# plt.xlabel("gamma")
# plt.ylabel("Fitness")
# plt.show()
# plt.plot(pop,df[df['gamma']==4.3]['Fitness'])
# plt.xlabel("popsize")
# plt.ylabel("Fitness")
# plt.show()