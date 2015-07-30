#!/bin/bash

root_dir=$PWD

DIRS=$(find $PWD -mindepth 1 -maxdepth 1 -type d)

solvent=$(echo $(basename $PWD) | awk -F "_" '{print $3}')

for d in $DIRS
    do
        cd $d/gausssum2.2
        cp UVSpectrum.txt UV_Spectrum_$(basename $d)_$d_$solvent.txt
        mv UV_Spectrum_$(basename $d)_$d_$solvent.txt /home/gclenden/Documents/Vanadium_Library/Optical_Spectra/VOLF/Optical_Spectra_Output

    done
