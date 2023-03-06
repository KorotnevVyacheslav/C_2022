import csv
import matplotlib.pyplot as plt

data1 = []
data2 = []

with open('data/data_1.txt', newline='\n') as File:
    reader = csv.reader(File, delimiter = " ")
    i = 0
    for row in reader:
        #print(row)
        iter = []

        if (i > 2):
            #iter.append(float(row[0]))
            #iter.append(float(row[3]))
            data1.append(float(row[3]))
            data2.append(float(row[4]))
        i+=1

plt.plot(data1, label='magnet', linewidth=3, color = 'black')
#plt.plot(data2, label='energy', linewidth=3, color = 'red')
plt.xlabel('Time')
plt.ylabel('Magnet')
plt.legend(fontsize=20)

plt.show()
