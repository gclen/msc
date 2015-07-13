#!/usr/bin/python

from collections import defaultdict

#Read the coordinates into a dictionary
def get_coords(xyz_file):

    #Initialize a dictionary to store the coordinates
    coords_dict=defaultdict(list)

    #Open the file 
    xyz_input_file=open(xyz_file,'r')

    #Skip the Link0, route, title and charge/multiplicity sections
    for _ in range(2):
        next(xyz_input_file)

    for line in xyz_input_file:
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

#Write out the gaussian input file
def write_gjf(coords_dict, solvent):

    input_file = open('input.gjf', 'w')

    resources = '%nprocshared=4\n%mem=4GB\n%chk=cisa.chk\n'
    
    if solvent != 'Gas Phase':
        route_section = '#p HSEh1PBE/GEN PSEUDO=READ opt SCRF=(Solvent=%s)\n' % (solvent)
    else:
        route_section = '#p HSEh1PBE/GEN PSEUDO=READ opt \n'

    #Write out file
    input_file.write(resources)
    input_file.write(route_section)
    input_file.write('\nTitle\n\n')
    input_file.write('0 1\n')

    for atom in coords_dict.keys():
        for coords in coords_dict[atom]:
            coords_string = '%s %s %s %s\n' % (atom, str(coords[0]).rjust(15), str(coords[1]).rjust(15),str(coords[2]).rjust(15))
            input_file.write(coords_string)

    input_file.write('\n')

    if 'V' in coords_dict.keys():
        input_file.write('V 0\nLANL2DZ\n****\n')
    
    atom_string=''
    for atom in coords_dict.keys():
        if atom != 'V':
            atom_string+=atom+' '
    atom_string+='0\n6-31+G*\n****\n\n'
    
    input_file.write(atom_string)

    if 'V' in coords_dict.keys():
        input_file.write('V 0\nLANL2DZ\n')
  
    input_file.write('\n\n\n\n')

    input_file.close()

if __name__=="__main__":

    xyz_file = raw_input("Please enter xyz file: ")
    solvent = raw_input("Please enter solvent: ") or "Gas Phase"

    coords_dict = get_coords(xyz_file)
    write_gjf(coords_dict, solvent)


