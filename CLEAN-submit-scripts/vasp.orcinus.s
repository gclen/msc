#!/bin/bash
#PBS -l walltime=240:00:00
#PBS -l pmem=2000mb
#PBS -r n
#PBS -l procs=224
#PBS -N "BNAl111_rel"

cd $PBS_O_WORKDIR
echo -n "START " > datefile
date >> datefile

#A bug on the Orcinus compiled version of VASP requires that WAVECAR and CHGCAR exist prior to execution, even if they are empty.
touch WAVECAR
touch CHGCAR

#Load the MPI modules
module purge
module load intel-2011


dir=`pwd`
ndir="${dir}_1"

#Run
mpiexec /global/software/VASP5/vasp-5.3.3/vasp > ./log

