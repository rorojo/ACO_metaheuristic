import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns




df = pd.read_csv('tiempo1.csv', header=None)

#antf
#1-12h
#2-24h
#3-48h
#4-72h
#5-96h

df2 = pd.read_csv('tiempo2.csv', header=None) 

#antRank
#1-12h
#2-24h
#3-48h
#4-72h
#5-96h

df3 = pd.read_csv('tiempo3.csv', header=None) 

#antf y antRank
#1-12h
#2-24h
#3-48h
#4-72h
#5-96h

#df1 = pd.read_csv('tiempo48us24h100v.csv', header=None)
#df2 = pd.read_csv('tiempo48us48h100v.csv', header=None)
#df3 = pd.read_csv('tiempo48us48h100v2.csv', header=None)
#df4 = pd.read_csv('tiempo48us72h100v.csv', header=None)







fig1, ax1 = plt.subplots()
#ax1.set_title('Basic Plot')
ax1.boxplot(df3)

p = df2.ix[4]  # select row
print(p.describe())


#plt.show()
