#!/usr/bin/python

import math 
import numpy as np

def bin_gaussian(f,trans_v,fwhm_v,del_v,v):

    eps_v=(2.175e8/fwhm_v)*f*(math.erf((2.772)*(v+del_v-trans_v)/(fwhm_v))-math.erf((2.772)*(v-trans_v)/(fwhm_v)))

    return eps_v



fwhm_v=6000
del_v=5

#v=23598.33248

tot_eps=0

trans_list=[(22112.64896,0.0324),(23174.08192,0.0552),(23598.33248,0.1075),(25248.55424,0.0585)]

for trans in trans_list:
    for v in range(20000,25000,del_v):   
        print "ERF is"
        print bin_gaussian(trans[1],trans[0],fwhm_v,del_v,v)
        tot_eps+=bin_gaussian(trans[1],trans[0],fwhm_v,del_v,v)

print "Tot is"
print tot_eps

