#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

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

def find_peak_position(uv_data):

    slice_index = next(i for i, tup in enumerate(uv_data) if tup[0]>325)
    
    #Unpack uv_data into two lists
    wavelength, absorp = zip(*uv_data[slice_index:])

    #Find the index of the max absorption
    max_absorp = max(absorp)
    peak_index = next(i for i, j in enumerate(absorp) if j==max_absorp)
    
    peak_wavelength = wavelength[peak_index]
    peak_absorp = absorp[peak_index]

    return (peak_wavelength, peak_absorp)

def plot_spectra(peak_point, uv_data):

    peak_wavelength = peak_point[0]
    peak_absorp = peak_point[1]
    
    wavelength, absorp = zip(*uv_data)

    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    plt.scatter(wavelength, absorp)
    
    plt.hlines(peak_absorp, 250, peak_wavelength, linestyles='dotted')
    plt.vlines(peak_wavelength, 0, peak_absorp, linestyles='dotted')

    plt.xlim(250,900)
    
    #Reset yaxis
    ymin, ymax = plt.ylim()
    plt.ylim(0,ymax)
    

    plt.show()

if __name__=="__main__":
    
    uv_file_name = 'VOLF_F_THF_uv_vis.txt'

    uv_data = parse_uv_file(uv_file_name)

    peak_point = find_peak_position(uv_data)

    plot_spectra(peak_point, uv_data)

