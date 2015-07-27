#!/usr/bin/python

import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import glob

def parse_uv_file(uv_file_name):
    
    #Initialize variables
    uv_data = []

    uv_file = open(uv_file_name, 'r')

    #Skip the first line
    next(uv_file)

    for line in uv_file:
        line_split = line.split()

        #Store the uv vis data as (wavelength, absorptance)
        uv_data.append((float(line_split[1]), float(line_split[2])))

    #Sort the list in order of wavelength 
    uv_data.sort(key=lambda tup: tup[0])

    return uv_data

def get_ligand(uv_file_name):

    file_split = uv_file_name.split('_')

    #Get the name of the ligand
    lig = file_split[3]

    return lig

def get_solvent(uv_file_name):

    file_split = uv_file_name.split('_')
    
    sol = (file_split[-1].split('.'))[0]

    return sol

def find_peak_position(uv_data, uv_file_name):

    #Get ligand and solvent names
    ligand = get_ligand(uv_file_name)
    solvent = get_solvent(uv_file_name)

    slice_index = next(i for i, tup in enumerate(uv_data) if tup[0]>350)
    
    #Unpack uv_data into two lists
    wavelength, absorp = zip(*uv_data[slice_index:])

    #Find the index of the max absorption
    max_absorp = max(absorp)
    peak_index = next(i for i, j in enumerate(absorp) if j==max_absorp)
    
    peak_wavelength = wavelength[peak_index]
    peak_absorp = absorp[peak_index]

    return (ligand, solvent, peak_wavelength, peak_absorp)

def find_ref_peak(ref_lig, ref_sol, peak_point_list):
   
    for peak in peak_point_list:

        #If the ligand and solvent match then set the reference wavelengths and absorptions
        if peak[0] == ref_lig and peak[1] == ref_sol:
            ref_wavelength = peak[2]
            ref_abs = peak[3]
   
    try:  
        return (ref_wavelength, ref_abs)
    except UnboundLocalError:
        sys.exit("Reference ligand or solvent is not valid")

def plot_spectra(peak_point, uv_data, uv_file_name):

    plot_file_name = os.path.splitext(uv_file_name)[0] + '.svg'

    peak_wavelength = peak_point[0]
    peak_absorp = peak_point[1]
    
    wavelength, absorp = zip(*uv_data)

    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    plt.scatter(wavelength, absorp, c='r', marker='.', linewidth=0.0)
    
    plt.hlines(peak_absorp, 250, peak_wavelength, linestyles='dotted')
    plt.vlines(peak_wavelength, 0, peak_absorp, linestyles='dotted')

    plt.xlim(250,900)
    
    #Reset yaxis
    ymin, ymax = plt.ylim()
    plt.ylim(0,ymax)

    plt.xlabel('Wavelength [nm]')
    plt.ylabel('Absorptance [L/mol{$\cdot$}cm]')

    plt.savefig(plot_file_name)

    plt.close()

if __name__=="__main__":
   

    peak_point_list = []

    for uv_file_name in glob.glob('*.txt'):

        uv_data = parse_uv_file(uv_file_name)

        peak_point = find_peak_position(uv_data, uv_file_name)

        peak_point_list.append(peak_point)

    test_tup = find_ref_peak('F', 'THF', peak_point_list)

