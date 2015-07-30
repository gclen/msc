#!/usr/bin/python

import os
import sys
import numpy as np
from scipy.signal import argrelextrema
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
    
    #Unpack uv_data into two lists
    wavelength, absorp = zip(*uv_data)
    
    max_indices = argrelextrema(np.asarray(absorp), np.greater)

    for i in max_indices[0]:
        idx = int(i)
        
        if wavelength[idx]>350:
            peak_wavelength = wavelength[idx]
            peak_absorp = absorp[idx]

    return (ligand, solvent, peak_wavelength, peak_absorp)

def find_ref_peak(peak_point_list):
    
    #Separate the tuples in to lists
    lig_list, sol_list, peak_wavelength_list, peak_absorp_list = zip(*peak_point_list)

    #Find the median wavelength
    med =  np.median(peak_wavelength_list)
    #Get the index of the median wavelength
    i = (np.abs(peak_wavelength_list - med)).argmin()
    
    return (lig_list[i], sol_list[i], peak_wavelength_list[i], peak_absorp_list[i])

def peak_percent_diff(peak, ref_wavelength, ref_abs):

    wavelength_diff = ((peak[2]-ref_wavelength)/(ref_wavelength))*100.0
    absorp_diff = ((peak[3]-ref_abs)/(ref_abs))*100.0
    
    #Change the label to Solvent-Ligand
    if peak[1] == 'GasPhase':
        peak_label = 'GP-'+peak[0]
    else:
        peak_label = peak[1]+'-'+peak[0]

    return (peak_label, wavelength_diff, absorp_diff)

def plot_spectra(peak_point, uv_data, uv_file_name):

    plot_file_name = os.path.splitext(uv_file_name)[0] + '.svg'

    peak_wavelength = peak_point[2]
    peak_absorp = peak_point[3]
    
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

def plot_peak_diff(peak_diff_list):

    peak_label_list, wavelength_diff_list, abs_diff_list = zip(*peak_diff_list)

    peak_label_list = list(peak_label_list)
    wavelength_diff_list = list(wavelength_diff_list)
    abs_diff_list = list(abs_diff_list)

    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    plt.xlabel('Peak wavelength difference [\%]')
    plt.ylabel('Peak absorption difference [\%]')

    plt.scatter(wavelength_diff_list, abs_diff_list, )

    for i, label in enumerate(peak_label_list):
        plt.annotate(label, (wavelength_diff_list[i],abs_diff_list[i]))

    plt.show()

if __name__=="__main__":
   
    peak_point_list = []
    peak_diff_list = []
    input_sol = 'THF'

    for uv_file_name in glob.glob('*.txt'):

        solvent = get_solvent(uv_file_name)    
         
        if solvent == input_sol: 
            uv_data = parse_uv_file(uv_file_name)

            peak_point = find_peak_position(uv_data, uv_file_name)

            peak_point_list.append(peak_point)


    ref_lig, ref_sol, ref_wavelength, ref_abs = find_ref_peak(peak_point_list)

    
    for peak in peak_point_list:
        peak_diff = peak_percent_diff(peak, ref_wavelength, ref_abs)
        peak_diff_list.append(peak_diff)    


    plot_peak_diff(peak_diff_list)
    

