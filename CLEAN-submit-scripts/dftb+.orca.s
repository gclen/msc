#!/bin/bash
sqsub --mpp="2G" -r 4d -j run_name -q threaded -n 8 -o output.log -i dftb_in.hsd ~/bin/dftb+
