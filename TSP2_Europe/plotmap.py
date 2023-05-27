import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import pandas as pd

img = mpimg.imread('Europe_topography_map.png')
df = pd.read_csv("Europe_cities.txt", sep=None, header=None)

fig = plt.figure(dpi=250)
plt.imshow(img)
plt.plot(df[1],df[2],'ko', ms=3)
plt.show()