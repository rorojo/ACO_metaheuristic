from numpy import *
import matplotlib.pyplot as plt
import matplotlib
 
def city_read():
#    int i
    x,y=loadtxt('city_data1.txt',int, unpack = True)
#    order=loadtxt('Data_rank.txt', int)
    order=loadtxt('Data.txt', int)
    print order
    print x
    print y
    '''order1[]
    x1[]
    y1[]'''

    x1=[]
    y1=[]
    for i in order:
        x1.append(x[i])
        y1.append(y[i])
    x1.append(x[order[0]])
    y1.append(y[order[0]])

    plt.plot(x1,y1, marker='o', linestyle = '-.', color = 'b')
    for i in range(len(order)):
        plt.text(x1[i],y1[i],(0+order[i])) #sumo 1 para obtener el mismo orden que en el archivo city_data.txt
    plt.show()
 
def main():
    city_read()

if __name__=="__main__":
    main()
