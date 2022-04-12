import numpy  as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('samples.txt')
data2 = np.loadtxt('samples_get.txt')

plt.plot(data1)
plt.plot(data2)
plt.show()