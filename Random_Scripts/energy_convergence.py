#!/usr/bin/python

#Import numpy
import numpy as np
#Import matplotlib for plotting
import matplotlib.pyplot as plt

tot_energies=[]

#Open the G09 output file 
log_file=open('output.log','r')

for line in log_file:

    if "SCF Done" in line:
        line_split=line.split()
        tot_energies.append(float(line_split[4]))
#Remove the first step since the guess is always terrible
tot_energies.pop(0)
#Adjust the step number since we have removed the first element
x_range=range(1,len(tot_energies)+1)

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

#plt.xlim(0,len(tot_energies))

#for i in range(1,len(tot_energies)):
#    plt.plot(i,tot_energies[i],marker='o',color='b',linestyle='-')

plt.plot(x_range,tot_energies,marker='o',color='b',linestyle='-')
plt.xlim(left=1)
plt.xlabel("SCF Step")
plt.ylabel(r"Total Energy [Ha]")

#plt.show()
plt.savefig('energy_convergence.svg')





