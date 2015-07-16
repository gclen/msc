#!/bin/bash

root_dir=$PWD

DIRS=$(find $PWD -type d)

for d in $DIRS
    do
        if [ -r "${d}/input.gjf" ]    
        then
            cd $d
            qsub gaussian.p
        fi


    done
