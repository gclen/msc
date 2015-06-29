#!/bin/bash

for i in {11..20}
do
mkdir Init_Velocity_$i
cd Init_Velocity_$i
cp ../input_part1 ../input_part2 ../qchem_SOF.s .
/home/gclenden/git/bash-scripts/./Random_Velocity_QCHEM
cat input_part1 Init_Velocity_Num input_part2 >input.in
qsub qchem_SOF.s
rm input_part1 input_part2 Init_Velocity_Num
cd ..
done
