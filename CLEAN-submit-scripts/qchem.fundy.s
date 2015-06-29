#!/bin/tcsh
# Use the tc shell instead of bash
#$ -S /bin/tcsh
# Set the amount of memory allocated for local scratch
#$ -l lscratch=2G
#$ -cwd
#$ -j y
# Set your job name here
#$ -N awesome_name_here
# Set the runtime in hours:minutes:seconds
#$ -l h_rt=48:00:00
# Set the max amount of virtual memory allocated for your job 
#$ -l h_vmem=3G
# Set the number of cores to use 
#$ -pe ompi* 4

setenv QC /usr/local/qchem
source $QC/bin/qchem.setup
setenv QCSCRATCH `pwd` #$TMPDIR
# Environment info is dumped to info.txt
env >> info.txt
setenv PATH /usr/local/qchem/bin:$PATH
# Set the name of your input and output files here
# The NSLOTS environment variable is the number of cores
# Use this variable instead of putting an explicit number 
qchem -np $NSLOTS input.in output.out


