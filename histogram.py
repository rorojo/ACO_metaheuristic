#import matplotlib.pyplot as plt
#import numpy as np

#import plotly.plotly as py
## Learn about API authentication here: https://plot.ly/python/getting-started
## Find your api_key here: https://plot.ly/settings/api

#gaussian_numbers = np.random.randn(1000)
#plt.hist(gaussian_numbers)
#plt.title("Gaussian Histogram")
#plt.xlabel("Value")
#plt.ylabel("Frequency")

#fig = plt.gcf()

#plot_url = py.plot_mpl(fig, filename='mpl-basic-histogram')

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
import matplotlib
import pandas as pd

#data = np.read_csv('Data1.txt')

#df = pd.read_csv('ex1.csv')

df = pd.read_csv('tiempo.csv', header=None)

print df





##data=loadtxt('Data1.txt',int, unpack = True)


## Fixing random state for reproducibility
#np.random.seed(19680801)

#N_points = 100000
n_bins = 30

## Generate a normal distribution, center at x=0 and y=5
#x = np.random.randn(N_points)
#y = .4 * x + np.random.randn(100000) + 5

#fig, axs = plt.subplots(1, 2, sharey=True, tight_layout=True)

## We can set the number of bins with the `bins` kwarg
plt.hist(df, bins=n_bins)
#axs[1].hist(y, bins=n_bins)



plt.xlabel('Mejor camino')
plt.ylabel('Frecuencia')
plt.title('Histogram of IQ')
#plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
plt.axis([34500, 38000, 0, 55])
plt.grid(True)
plt.show()







plt.show()
