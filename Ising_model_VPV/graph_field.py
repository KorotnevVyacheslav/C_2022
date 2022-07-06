import csv
import matplotlib.pyplot as plt
import numpy as np

data1 = [[],[],[]]
data2 = [[],[],[]]

with open('magnet_field.txt', newline='\n') as File:
    reader = csv.reader(File, delimiter=' ')
    for row in reader:
        #temp = [float(row[0]),float(row[1]),float(row[0]) * float(row[2])]
        data1[0].append(float(row[0]))
        data1[1].append(float(row[1]))
        data1[2].append(float(row[1]) * float(row[2]))

with open('magnet_temperature.txt', newline='\n') as File:
    reader = csv.reader(File, delimiter=' ')
    for row in reader:
        #temp = [float(row[0]),float(row[1]),float(row[0]) * float(row[2])]
        data2[0].append(float(row[0]))
        data2[1].append(float(row[1]))
        data2[2].append(float(row[1]) * float(row[2]))

def func(T, H):
    return np.tanh(H/T)

t = np.arange(0., 8., 0.1)
h = np.arange(-4., 4., 0.1)

plt.rcParams['font.size'] = '16'

plt.subplot(121)
plt.errorbar(data1[0],data1[1], yerr=data1[2], label='magnet', linewidth=3, color = 'black')
plt.plot(h, func(2, h), color='red', linewidth=3)

plt.xlabel('Magnetic field')
plt.ylabel('Manetization')
plt.legend(fontsize=20)

plt.subplot(122)
plt.errorbar(data2[0],data2[1], yerr=data2[2], label='magnet', linewidth=3, color = 'black')
#plt.plot(t, func(t, -0.5), color='red', linewidth=3)
#plt.plot(data1[0],data1[1])

plt.xlabel('Temperature')
plt.ylabel('Manetization')
plt.legend(fontsize=20)

plt.show()
