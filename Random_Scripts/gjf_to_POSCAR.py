#!/usr/bin/python

import sys 
import re
from collections import defaultdict

#Get the total number of lines to skip 
def skip_Lines(gjf_file):
    
    #Set the line skip counter to 0
    counter=0

    gaussian_input_file=open(gjf_file,'r')

    #Get the number of initial lines to skip 
    for line in gaussian_input_file:
        #Look for Link0 or route section lines
        if re.search('%|#',line):
            #Increment the counter
            counter+=1
    #Close the file 
    gaussian_input_file.close()
    #Return the counter +4 to give number of lines to skip 
    return counter+4

#Read the coordinates into a dictionary
def get_Coords(gjf_file,header_count):
    
    #Initialize a dictionary to store the coordinates
    coords_dict=defaultdict(list)

    #Open the file 
    gaussian_input_file=open(gjf_file,'r')

    #Skip the Link0, route, title and charge/multiplicity sections
    for _ in range(header_count):
        next(gaussian_input_file)

    for line in gaussian_input_file:
        #Break out of the loop at a blank line 
        if not line.strip():
            break
        else:
            line_split=line.split()
            #Add the coordinates into a tuple
            coords=(float(line_split[1]),float(line_split[2]),float(line_split[3]))
            #Put it into the dictionary 
            coords_dict[line_split[0]].append(coords)
    
    #Return the dictionary
    return coords_dict

#Determine the proper supercell size 
def get_supercell_Size(coords_dict):
    
    #Initialize lists to store the coordinates
    x_coords=[]
    y_coords=[]
    z_coords=[]

    #Loop over all atoms
    for atom in coords_dict.keys():
        #Loop over all sets of coordinates
        for coord_set in coords_dict[atom]:
            #Add the coordinates to their respective lists
            x_coords.append(coord_set[0])
            y_coords.append(coord_set[1])
            z_coords.append(coord_set[2])

    #Get the max,min and range of the lists 
    x_min=min(x_coords)
    x_max=max(x_coords)
    x_range=x_max-x_min

    y_min=min(y_coords)
    y_max=max(y_coords)
    y_range=y_max-y_min

    z_min=min(z_coords)
    z_max=max(z_coords)
    z_range=z_max-z_min   

    #Add 10 angstroms to each side of the supercell 
    supercell_lengths=(x_range+10.0,y_range+10.0,z_range+10.0)

    return supercell_lengths

def write_POSCAR(coords_dict,supercell_lengths):
    
    #Open up the POSCAR file for writing
    POSCAR_file=open('POSCAR','w')

    #Put all the atom names into a string 
    atom_string=''
    atom_count_string=''

    for atom_name in coords_dict.keys():
        atom_string=atom_string+' '+atom_name
        atom_count_string=atom_count_string+' '+str(len(coords_dict[atom_name]))

    #Write the atom names 
    POSCAR_file.write(atom_string+'\n')
    #Write the scaling number 
    POSCAR_file.write('    1.00000000000000 \n')
    #Write the supercell vectors
    super_x='    %s   0.00000    0.00000 \n' % (str(supercell_lengths[0]))
    super_y='    0.00000    %s    0.00000 \n' % (str(supercell_lengths[1]))
    super_z='    0.00000    0.00000    %s \n' % (str(supercell_lengths[2]))

    POSCAR_file.write(super_x)
    POSCAR_file.write(super_y)
    POSCAR_file.write(super_z)

    #Write a line with the number of each atom
    POSCAR_file.write(atom_count_string+'\n')
    #Write the type of the coordinates (Cartesian or direct)
    POSCAR_file.write('Cartesian \n')

    #Write out the coordinates 
    #Loop over the coordinates dictionary     
    for atom in coords_dict.keys():
        for coords_set in coords_dict[atom]:
            coord_string=' %s %s %s \n' % (str(coords_set[0]),str(coords_set[1]),str(coords_set[2]))
            POSCAR_file.write(coord_string)
        
    #Close the POSCAR file 
    POSCAR_file.close()
    

if __name__=="__main__":
    
    #Get the gaussian input file name
    gjf_file=sys.argv[1]
    
    #Get the number of lines to skip 
    header_count=skip_Lines(gjf_file)
    #Read the coordinates into a dictionary 
    coords_dict=get_Coords(gjf_file,header_count)

    supercell_lengths=get_supercell_Size(coords_dict)
        
    write_POSCAR(coords_dict,supercell_lengths)
