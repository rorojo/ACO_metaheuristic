import tempfile,os.path
import pandas as pd
import numpy as np

#data = np.random.rand(20)
data = pd.read_csv('Data1.txt')

#fig, axes = plt.subplots(2, 1)

#data.plot.bar(ax=axes[0], color='k', alpha=0.7)
#data.plot.barh(ax=axes[1], color='k', alpha=0.7)

#data['data'].plot.hist(bins=50)

#bins = [18, 25, 35, 60, 100]
c = pd.cut(data, 2 , precision=2 )
print c


