#!/bin/bash

awk '/TIME STEP/,/Nuclear Repulsion Energy/' output.out > coords_1
awk '/1      V/,/44      F/' coords_1 >coords_cut
sed -i '/1      V/i 44 44' coords_cut
sed '/44 44/a \ ' coords_cut > coords_afterspace
awk '{print $2, $3, $4, $5}' coords_afterspace > VOLF_BOMD_Visual_i.xyz

rm coords_1 coords_cut coords_afterspace


