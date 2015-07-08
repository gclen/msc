#!/usr/bin/python

#Import numpy
import numpy as np
#Import matplotlib for plotting
import matplotlib.pyplot as plt

scaled_list=[]
scaled_temp_list=[]

data_file=open('projected_sums.txt','r')

for line in data_file:
    line_split=line.split()
    
    if line_split[0]=='---':
        scaled_list.append([energy,scaled_temp_list])
        scaled_temp_list=[]
    else:
        energy=float(line_split[0])
        
        scaled_temp_list.append([float(line_split[1]),float(line_split[2])])  


    
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

plt.xlim((-5,20))
for i in range(len(scaled_list)):
    for j in range(len(scaled_list[i][1])):
        
        if (i+1<len(scaled_list)) and scaled_list[i][0]==scaled_list[i+1][0]:
            scaled_list[i][0]-=0.1
            scaled_list[i+1][0]+=0.1
            #Get the min and max values of the x axis 
            xmin,xmax=plt.xlim()
            #Add a label indicating the energy shift for degeneracy 
            plt.text(xmin+1,scaled_list[i][0],'Shifted for \ndegeneracy')            
        
        plt.scatter(scaled_list[i][1][j][0],scaled_list[i][0],color=str(scaled_list[i][1][j][1]))


plt.xlabel("Distance along v [\AA]")
plt.ylabel(r"Energy [eV]")

#Set the xtics range
xticks_list=range(0,16,5)
#Append the right edge of the box
xticks_list.append(11.9)
xticks_labels=[str(i) for i in range(0,16,5)]
xticks_labels.append('')

#Get yrange
ymin,ymax=plt.ylim()
#Put vertical lines at the edges of the box
plt.vlines([0,11.9],ymin,ymax,linestyles='dashed')

#Put vertical lines at atom positions
#Read atoms
atom_file=open('atom_projections.txt','r')

atom_points=[]

for atom in atom_file:
    atom_split=atom.split()      
    atom_points.append(atom_split[1])

#Get desired atom indices
desired_atom_index=[1,2]
#Store positions in a list
desired_atoms=[]

for index in desired_atom_index:
    desired_atoms.append(atom_points[index-1])          

plt.vlines(desired_atoms,ymin,ymax,linestyles='dotted')

#Change the yrange 
plt.ylim((ymin,ymax))

plt.xticks(xticks_list,xticks_labels)

    

plt.show()
#plt.savefig('level_diagram_LiH.svg')

