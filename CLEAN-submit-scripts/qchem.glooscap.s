#!/bin/tcsh
# Use the t shell instead of bash
#$ -S /bin/tcsh
#$ -cwd
#$ -j y
# Set the name of your job here
#$ -N awesome_name_here
# Set the name of the OS
# Due to licensing issues it only seems to work with this OS on glooscap
#$ -l os=RHEL4
# Set the runtime in hours:minutes:seconds
#$ -l h_rt=00:10:00
# Set the hard limit of virtual memory
#$ -l h_vmem=2G
# Set the number of cores to use
#$ -pe ompi* 1 

setenv QC /usr/local/qchem
source $QC/bin/qchem.setup
setenv QCSCRATCH `pwd` #$TMPDIR
setenv QCLOCALSCR $TMPDIR
# Environment info is dumped to env_info.txt 
env >> env_info.txt
setenv PATH /usr/local/qchem/bin:$PATH
# Set the name of your input and output files here
# The NSLOTS environment variable is the number of cores
# Use this variable instead of putting an explicit number 
qchem -np $NSLOTS input.in output.out




