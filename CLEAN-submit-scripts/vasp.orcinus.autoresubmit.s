#!/bin/bash
#PBS -l walltime=240:00:00
#PBS -l pmem=2000mb
#PBS -r n
#PBS -l procs=80
#PBS -M kyle.mills@uoit.net
sleeptime="238h"
#PBS -N undoped_MD

cd $PBS_O_WORKDIR
echo -n "START " > datefile
date >> datefile

touch WAVECAR
touch CHGCAR

module purge
module load intel-2011

dir=`pwd`
ndir="${dir}_1"

mpiexec /global/software/VASP5/vasp-5.3.3/vasp > ./log &


##The following lines pause script execution for $sleeptime and then
# issues VASP a stop command.  It then clones the job to a new directory 
# (appending a "_1", copies the CONTCAR to the POSCAR and then resubmits 
# the job.  This is useful for MOLECUlAR DYNAMICS where several smaller 
# jobs might queue and run faster than fewer larger jobs.


## MAKE SURE THAT YOU MONITOR THE JOB TO ENSURE THAT VASP IS ACTUALLY
#  RUNNING.  IF VASP CRASHES, THE SLEEP COMMAND WILL PREVENT ANY CORES FROM
#  BEING RELEASED UNTIL THE WALLTIME EXPIRES, WASTING RESOURCES.  CHECK AFTER A FEW HOURS TO MAKE SURE THAT VASP IS ACTUALLY WRITING FILES.

#Pause for $sleeptime.  You want this to be a bit less than walltime so VASP
# has time to exit cleanly. (e.g. walltime - (2 hours))
sleep $sleeptime

echo -n "ISSUING STOP COMMAND" >> datefile
date >> datefile
echo "LSTOP=.TRUE." > STOPCAR

#Wait for VASP to exit cleanly.  If it has not exited cleanly, clone it anyway. We'll just be missing the last timestep.
sleep 1h
sleep 50m

echo -n "CLONING JOB" >> datefile
date >>datefile

#Make a new directory
mkdir $ndir
#Copy all necessary files (modify for your particular application)
cp $dir/CONTCAR  $ndir/POSCAR
cp $dir/vasp.s   $ndir/vasp.s  #submit script
cp $dir/POTCAR   $ndir/POTCAR
cp $dir/INCAR    $ndir/INCAR
cp $dir/KPOINTS  $ndir/KPOINTS
#Two files that Kyle wants in all directories...
#  add/remove/modify for yourself.
cp $dir/plot.sh  $ndir/plot.sh
cp $dir/clean.sh $ndir/clean.sh

#change to the new directory and resubmit the job
cd $ndir
qsub vasp.s

