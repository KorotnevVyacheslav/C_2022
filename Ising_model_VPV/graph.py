import csv
import matplotlib.pyplot as plt

data1 = []
data2 = []

with open('magnet.txt', newline='\n') as File:
    reader = csv.reader(File)
    for row in reader:
        data1.append(float(row[0]))

with open('energy.txt', newline='\n') as File:
    reader = csv.reader(File)
    for row in reader:
        data2.append(float(row[0]))

plt.plot(data1, label='magnet', linewidth=3, color = 'black')
plt.plot(data2, label='energy', linewidth=3, color = 'red')
plt.xlabel('Time')
plt.ylabel('Magnet')
plt.legend(fontsize=20)

plt.show()
