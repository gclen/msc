#!/bin/tcsh
# Use t shell instead of bash
#$ -S /bin/tcsh
# Set the amount of memory allocated for local scratch 
#$ -l lscratch=2G
# Used to ignore certain nodes due to licensing issues with Qchem 
#$ -l h="!cl174&!cl053&!cl186"
#$ -cwd
#$ -j y
# Set the job name here
#$ -N awesome_name_here
# Set the max job run time in hours:minutes:seconds
#$ -l h_rt=48:00:00
# Set the hard limit on virtual memory allocated
#$ -l h_vmem=3G
# Set the number of cores here
#$ -pe ompi* 4 

setenv QC /usr/local/qchem
source $QC/bin/qchem.setup
setenv QCSCRATCH `pwd` #$TMPDIR
setenv QCLOCALSCR $TMPDIR
# Environment info is dumped to info.txt
env >> info.txt
setenv PATH /usr/local/qchem/bin:$PATH
# Set the name of your input and output files here
# The NSLOTS environment variable is the number of cores
# Use this variable instead of putting an explicit number 
qchem -np $NSLOTS input.in output.out
