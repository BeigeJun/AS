import numpy as np
from sklearn.datasets import load_iris
import pandas as pd
import matplotlib.pyplot as plt
Iris = load_iris()


k = 3
fig = plt.figure()
centeroids_x = np.random.uniform(min(x), max(x), k)
centeroids_y = np.random.uniform(min(y), max(y), k)
centeroids_z = np.random.uniform(min(z), max(z), k)
centeroid = list(zip(centeroids_x, centeroids_y, centeroids_z))
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(centeroids_x, centeroids_y, centeroids_z, alpha=0.5, color="red")
plt.show()
