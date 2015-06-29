#!/bin/csh
# Use the C shell instead of bash
#$ -S /bin/csh
# Set the name of your job here
#$ -N awesome_name_here
#$ -m ae
# Set your email address here to receive email updates about job termination
#$ -M firstname.lastname+scheduler+update@uoit.net
#$ -j y
# Set the amount of memory required for your job (see calculation below)
# The nprocs and %mem values come from the gaussian input file 
#$ -l h_vmem=3.75G 
#  h_vmem = (%nprocs + 1) * (%mem + 1Gb) / (%nprocs)
#  (4 + 1) * (4. + 1)/(8.) = 3.75
#$ -cwd
# Set the runtime in hours:minutes:seconds
#$ -l h_rt=48:00:00
# Not used here but sometimes it is useful to set the flag -l test=true
# Used to submit to the test queue 
# Jobs must be less than an hour long
# Set the number of cores to use 
#$ -pe openmp 4 

date

hostname

limit datasize     unlimited
limit stacksize    10240 kbytes
limit memoryuse    unlimited
limit vmemoryuse   unlimited

setenv g09root /usr/local/gaussian
setenv GAUSS_SCRDIR $TMPDIR
source /usr/local/gaussian/g09/bsd/g09.login

setenv GAUSS_SCRDIR $SGE_O_WORKDIR

# Give the names of your input and output files here 
g09 < ./input.gjf > output.log

echo -n "Run finished at "
date
