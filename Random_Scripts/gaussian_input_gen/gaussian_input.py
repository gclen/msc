#!/usr/bin/python

import os
import sys 
import argparse
from collections import defaultdict
import help_strings

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

def check_g09_termination(gaussian_log_file):
    
    norm_term = False

    output_file = open(gaussian_log_file, 'r')

    for line in output_file:
        if "Normal termination of Gaussian 09" in line:
            norm_term = True        

    return norm_term        

#Write out the gaussian input file
def write_scf_gjf(coords_dict, solvent, input_file_name, atom_pseudo, 
                  atom_pseudo_list, opt=False):

    input_file = open(input_file_name, 'w')

    resources = '%nprocshared=4\n%mem=4GB\n%chk=cisa.chk\n'
    
    if atom_pseudo == True:
        route_section = '#p HSEh1PBE/GEN PSEUDO=READ'
    else:
        route_section = '#p HSEh1PBE/6-31+G*'      

    if opt == True:
        route_section += ' opt'
    
    if (solvent != 'Gas Phase'):
        route_section += ' SCRF=(Solvent=%s)' % (solvent)

    route_section += '\n'

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

    if atom_pseudo == True:
        atom_pseudo_basis = ''
        atom_pseudo_ecp = ''    

        for atom in atom_pseudo_list:
            if atom in coords_dict.keys():
                atom_pseudo_basis += atom + ' '
                atom_pseudo_ecp += atom + ' '
    
        atom_pseudo_basis += '0\nLANL2DZ\n****\n'        
        atom_pseudo_ecp += '0\nLANL2DZ\n\n\n\n'

        input_file.write(atom_pseudo_basis)         
    
        atom_string=''
        for atom in coords_dict.keys():
            if atom not in atom_pseudo_list:
                atom_string+=atom+' '
        atom_string+='0\n6-31+G*\n****\n\n'
    
        input_file.write(atom_string)
        input_file.write(atom_pseudo_ecp)
    
    input_file.write('\n\n\n\n')
    
    input_file.close()

    return atom_pseudo

def write_spectra_gjf(coords_dict, solvent, input_file_name, atom_pseudo, atom_pseudo_list,
                      calc_label):

    input_file = open(input_file_name, 'w')

    resources = '%nprocshared=4\n%mem=4GB\n%chk=cisa.chk\n'

    if atom_pseudo == True:
        route_section = '#p HSEh1PBE/GEN PSEUDO=READ'
    else:
        route_section = '#p HSEh1PBE/6-31+G*'      
    
    if (solvent != 'Gas Phase'):
        route_section += ' SCRF=(Solvent=%s)' % (solvent)
    
    if calc_label == 'pop':
        route_section += ' guess=read geom=allcheck pop=full iop(3/33=1,3/36=-1) \n\n'  
    elif calc_label == 'tddft':
        route_section += ' guess=read geom=allcheck td(nstates=90) iop(9/40=2) iop(6/8=3) density=rhoci \n\n'                 

    #Write out file
    input_file.write(resources)
    input_file.write(route_section)

    if atom_pseudo == True:
        atom_pseudo_basis = ''
        atom_pseudo_ecp = ''    

        for atom in atom_pseudo_list:
            if atom in coords_dict.keys():
                atom_pseudo_basis += atom + ' '
                atom_pseudo_ecp += atom + ' '
    
        atom_pseudo_basis += '0\nLANL2DZ\n****\n'        
        atom_pseudo_ecp += '0\nLANL2DZ\n\n\n\n'

        input_file.write(atom_pseudo_basis)         
    
        atom_string=''
        for atom in coords_dict.keys():
            if atom not in atom_pseudo_list:
                atom_string+=atom+' '
        atom_string+='0\n6-31+G*\n****\n\n'
    
        input_file.write(atom_string)
        input_file.write(atom_pseudo_ecp)
    
    input_file.write('\n\n\n\n')
    
    input_file.close()

def write_gjf(coords_dict, solvent, type_calc):

    #Boolean variable that denotes existence of atoms that require pseudopotentials
    atom_pseudo = False

    atom_pseudo_list = ['Sc', 'Ti', 'V', 'Cr', 'Mn', 'Fe', 'Co', 'Ni', 'Cu', 'Zn', 'Ga', 'Ge', 'As', 
                        'Se', 'Br', 'Kr', 'Rb', 'Sr', 'Y', 'Zr', 'Nb', 'Mo', 'Tc', 'Ru', 'Rh', 'Pd', 
                        'Ag', 'Cd', 'In', 'Sn', 'Sb', 'Te', 'I', 'Xe', 'Cs', 'Ba', 'La', 'Ce', 'Pr', 
                        'Nd', 'Pm', 'Sm', 'Eu', 'Gd', 'Tb', 'Dy', 'Ho', 'Er', 'Tm', 'Yb', 'Lu', 'Hf', 
                        'Ta', 'W', 'Re', 'Os', 'Ir', 'Pt', 'Au', 'Hg', 'Tl', 'Pb', 'Bi', 'Po', 'At', 
                        'Rn', 'Fr', 'Ra', 'Ac', 'Th', 'Pa', 'U', 'Np', 'Pu', 'Am', 'Cm', 'Bk', 'Cf', 
                        'Es', 'Fm', 'Md', 'No', 'Lr'] 

    #Check for atoms with d or f electrons
    for atom in atom_pseudo_list:
        if atom in coords_dict.keys():
            atom_pseudo = True 

    if type_calc == "relax":
        write_scf_gjf(coords_dict, solvent, 'input.gjf', atom_pseudo, atom_pseudo_list, opt=True)
    elif type_calc == "spectra":
        atom_pseudo = write_scf_gjf(coords_dict, solvent, 'input_1.gjf', 
                                    atom_pseudo, atom_pseudo_list)
        write_spectra_gjf(coords_dict, solvent, 'input_2.gjf', atom_pseudo, atom_pseudo_list, 'pop')
        write_spectra_gjf(coords_dict, solvent, 'input_3.gjf', atom_pseudo, atom_pseudo_list, 'tddft')

if __name__=="__main__":

    parser = argparse.ArgumentParser(description=help_strings.description)
    parser.add_argument("-s","--solvent", help=help_strings.solventhelp, default="Gas Phase")
    parser.add_argument("-t","--type_calc", help=help_strings.typehelp, default=None)
    parser.add_argument("-i","--input", help=help_strings.inputhelp, default=None)

    args = parser.parse_args()

    #Get file extension if the file is specified 
    try: 
        filename, file_ext = os.path.splitext(args.input)
        if file_ext not in (".xyz", ".log", ".out"):
            print "Invalid file type. File must be a xyz or G09 output file. "
            sys.exit()

    except AttributeError:
        print "No file given as input. Enter a xyz or G09 output file."

    #Get the type of calculation
    try: 
        type_calc = args.type_calc.lower()
    except AttributeError: 
        print "No calculation type specified."

    #Get coordinates
    if file_ext == ".xyz":
        xyz_file = args.input
    elif file_ext == (".log" or ".out"):
        
        norm_term = check_g09_termination(args.input)

        if norm_term == True:
            os.system("babel %s -o xyz g09_input_temp.xyz" % (args.input))
            xyz_file = "g09_input_temp.xyz"
        else:
            print "Gaussian did not terminate properly. Aborting."
            sys.exit()     

    coords_dict = get_coords(xyz_file)

    write_gjf(coords_dict, args.solvent, type_calc)
     
    #Delete temp xyz file 
    os.system('rm g09_input_temp.xyz')

