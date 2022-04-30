import numpy  as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('samples.txt')
data2 = np.loadtxt('decoder_output.txt')

err = np.sum(np.absolute(data1-data2))/(data1.size*(2**16)/100)

plt.plot(data1)
plt.plot(data2)
plt.figtext(0.7, 0.8, "Error: "+ "%.3f" % err +"%")
plt.show()