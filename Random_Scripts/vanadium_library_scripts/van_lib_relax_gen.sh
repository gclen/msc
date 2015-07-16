#!/bin/bash

root_dir=$PWD

DIRS=$(find $PWD -type d)

for d in $DIRS
    do
        if [ -r "${d}/input.gjf" ]    
        then
            sed -i 's/%nprocshared=4/%nprocshared=16/' input.gjf
            sed -i 's/%mem=4GB/%mem=6GB/' input.gjf
            cd $d
            cp ${root_dir}/gaussian.p .
            sed -i "s/JOB_NAME/$(basename $d)/" gaussian.p
        fi


    done
