#!/bin/bash

r_bond_0=0.942104
for i in {0..10}
do
r_bond=$(echo "scale=10; $r_bond_0+$i*0.1" | bc)

sed "s/r_init/$r_bond/" <input.gjf >input_$i.gjf
#more input_$i.gjf
mkdir Temp_dir_$i
cd Temp_dir_$i
cp ../gaussian.p ../input_$i.gjf .
sed "s/input.gjf/input_$i.gjf/" <gaussian.p >temp
sed "s/output.log/output_$i.log/" <temp >gaussian_$i.p
chmod a+x gaussian_$i.p
rm gaussian.p
qsub gaussian_$i.p
cd ..

done


rm input_*




