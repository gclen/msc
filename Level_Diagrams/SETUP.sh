#!/bin/bash

#Go into the source files directory 
cd Source_Files

#Compile the C++ code 
echo "Compiling..."
make

#Copy the gui files to the ase-gui directory
cp levels.py gui.py /usr/lib/python2.7/dist-packages/ase/gui

#Copy the executable C++ and python into /usr/local/bin
cp SOLD SOLD_plot.py cubegen /usr/bin

#Go up one directory to the original one
cd ../

echo "Done!"




