#!/usr/bin/python

import os
import subprocess

dir_name=os.getcwd().split('/')[-1]
solvents=['Benzene',"GasPhase","THF"]

for solvent in solvents:
    subprocess.call("mkdir %s_%s" % (dir_name,solvent),shell=True)


