random-scripts
============

Command line utility to generate Gaussian09 input files from xyz or gaussian output files. Requires python 2.7 and openbabel. To install openbabel on your local machine run 

$ sudo apt-get install openbabel

On a cluster you will probably need to load python 2.7 and openbabel. For example on placentia, add the following to your ~.bashrc

module load gcc python/2.7.2
module load gcc openbabel

To run, put gaussian_input.py and help_strings.py into your path. To see available command line arguments run

$ gaussian_input.py -h 






