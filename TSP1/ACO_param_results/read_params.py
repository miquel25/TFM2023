import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("ACO_params.txt", sep=' ')
df = df.sort_values('Fitness')
df