#!/usr/bin/python

import numpy as np

Trans_dip=open('transdipmom.txt','r')

E_0=0.0
init_state=1

for _ in range(4):
    next(Trans_dip)

for line in Trans_dip:

    line_split=line.split()
    
    #Get the starting energy
   
    if float(line_split[0])==init_state and float(line_split[1])==(init_state+1):
        E_0=float(line_split[5])

    if(float(line_split[0])==init_state and  float(line_split[1])>float(line_split[0])):
        
        x_coord=float(line_split[2])
        y_coord=float(line_split[3])
        z_coord=float(line_split[4]) 
        
        energy=float(line_split[5])

        Norm=np.sqrt(x_coord**2+y_coord**2+z_coord**2)
        
        print line_split[0],"->",line_split[1],Norm,energy 
        
        energy=float(line_split[5])   
        
        if(energy>=E_0+5.0):
            break
        









