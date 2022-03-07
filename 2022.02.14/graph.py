import numpy as np
import math
import matplotlib.pyplot as plt
import csv
from mpl_toolkits.mplot3d import Axes3D


data = []
X = []
Y = []
Xl = []
Yl = []

with open("results_square.txt", newline="\n") as csvfile:
    ar = csv.reader(csvfile, delimiter=" ")
    for row in ar:
        data.append(row)


for i in range(8):
    #X.append(math.log(float(i[0])))
    #Y.append(math.log(float(i[1])))
    X.append(float(data[i][0]))
    Y.append(float(data[i][1]))

'''
for i in data:
    Xl.append(math.log(float(i[0])))
    Yl.append(math.log(float(i[1])))
    X.append(float(i[0]))
    Y.append(float(i[1]))
'''

plt.plot(X, Y)
plt.show()
plt.plot(Xl, Yl)
plt.show()
