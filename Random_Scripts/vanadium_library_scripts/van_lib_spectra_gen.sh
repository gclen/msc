#!/bin/bash

root_dir=$PWD

DIRS=$(find $PWD -type d)

for d in $DIRS
    do
        if [ -r "${d}/output.log" ]    
        then
            cd $d 
            form_cisa.ch cisa.chk
            gaussian_input.py -i output.log -t spectra -s TetraHydroFuran
            sed -i 's/%nprocshared=4/%nprocshared=16/' input_*.gjf
            sed -i 's/%mem=4GB/%mem=6GB/' input_*.gjf
            mv input_* /home/gclenden/nqs/Vanadium_Library/Optical_Spectra/VOLF/VOLF_Spectrochemical_THF/$(basename $d) 
            cd /home/gclenden/nqs/Vanadium_Library/Optical_Spectra/VOLF/VOLF_Spectrochemical_THF/$(basename $d)
            cp /home/gclenden/nqs/Vanadium_Library/Optical_Spectra/gaussian.p .
            sed -i "s/JOB_NAME/$(basename $d)/" gaussian.p
        fi


    done
