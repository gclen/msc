#!/bin/tcsh

set file=$1

setenv g09root /usr/local/gaussian
setenv GAUSS_SCRDIR /globalscratch/$USER/
source /usr/local/gaussian/g09/bsd/g09.login
freqchk $file -o freqchk n 0 0 0 Y N

grep "Frequencies" freqchk | awk '/Frequencies/{print $3, $4, $5}'>Frequencies
grep "IR Inten" freqchk | awk '/IR Inten/{print $4, $5, $6}'>IR_Inten


wc -w Frequencies | awk '{print $1}' | cat Spectrum_Input.in



