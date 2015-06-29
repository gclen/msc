#!/bin/bash
#PBS -S /bin/bash
# Set the runtime in hours:minutes:seconds
#PBS -l walltime=168:00:00
# Set the amount to memory to be used
#PBS -l mem=4096MB
# Set the number of nodes and cores per node 
#PBS -l nodes=1:ppn=4
# Set your email here to be emailed about job execution and termination
#PBS -M some_email@uoit.net
#PBS -m bea
# Set the name of your job here
#PBS -N awesome_name_here
# Adjust the mem and ppn above to match the requirements of your job

cd $PBS_O_WORKDIR

echo "Current working directory is `pwd`"
echo "Running on `hostname`"
echo "Starting run at: `date`"

# Set up the Gaussian environment using the module command:
module load gaussian

# Run g09
# Give the names of the input and output files here
g09 < input_1.gjf > output.log




