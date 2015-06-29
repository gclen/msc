#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <complex>
#include <vector>
#include "Cube_Functions.h"

using namespace std;


double Cube_Norm(char Cube_File_Occupied[50])
{
	struct Voxel_Info Voxel_Values;	
	int Voxel_X,Voxel_Y,Voxel_Z;
        double Coeff_Sum;
	
        //Initialize variables
	Voxel_Values=Voxel_Read(Cube_File_Occupied);
	
	Voxel_X=Voxel_Values.Num_X;
	Voxel_Y=Voxel_Values.Num_Y;
	Voxel_Z=Voxel_Values.Num_Z;

        Coeff_Sum=0; 

	//Read in occupied cube file    
	vector<vector<vector<double> > > VolumetricData=Cube_Read(Cube_File_Occupied);
	
	//Square its contents
	vector<vector<vector<double> > > Cube_Squared=Square_Cubefile(Voxel_X,Voxel_Y,Voxel_Z,VolumetricData);

        //Sum the squared coefficients
         for (int ix=0;ix<Voxel_X;ix++) 
	    {
	      for (int iy=0;iy<Voxel_Y;iy++) 
	      {
		 for (int iz=0;iz<Voxel_Z;iz++) 
		 {
	  	 Coeff_Sum+=Cube_Squared[ix][iy][iz];
		 }
	      }
	    } 	





return Coeff_Sum;
}
