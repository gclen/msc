#!/bin/bash

r_bond_0=0.942104
for i in {0..10}
do
r_bond=$(echo "scale=10; $r_bond_0+$i*0.1" | bc)
cd Temp_dir_$i
grep "SCF Done" output_$i.log > Energy_$i.dat
mv Energy_$i.dat ../
cd ../
awk '/SCF/{print '$r_bond',$5}' Energy_$i.dat  > Data_$i.dat

done

for n in {0..10}
do 

cat Test_$((n)).dat Data_$n.dat > Test_$((n+1)).dat
rm Test_$n.dat
rm Data_$n.dat
rm Energy_$n.dat
done

cp Test_11.dat PES_Data.dat
rm Test_11.dat
rm -r Temp_dir_*

gnuplot "PES_Gnuplot.gp"


 
