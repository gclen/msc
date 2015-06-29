#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "Cube_Functions.h"

using namespace std;


vector<vector<vector<double> > > Transition(char Cube_File_Occupied[50], char Cube_File_Virtual[50],double Transition_Contribution,vector<vector<vector<double> > >& EDDM_Vector)
{
	struct Voxel_Info Voxel_Values;	
	int Voxel_X,Voxel_Y,Voxel_Z;
	

	Voxel_Values=Voxel_Read(Cube_File_Occupied);
	
	Voxel_X=Voxel_Values.Num_X;
	Voxel_Y=Voxel_Values.Num_Y;
	Voxel_Z=Voxel_Values.Num_Z;


	//Read in occupied cube file    
	vector<vector<vector<double> > > VolumetricData=Cube_Read(Cube_File_Occupied);
	
	//Square its contents
	vector<vector<vector<double> > > Occupied_Squared=Square_Cubefile(Voxel_X,Voxel_Y,Voxel_Z,VolumetricData);

	//Read in virtual cube file 
	VolumetricData=Cube_Read(Cube_File_Virtual);

	//Square its contents
	vector<vector<vector<double> > > Virtual_Squared=Square_Cubefile(Voxel_X,Voxel_Y,Voxel_Z,VolumetricData);


	//Update EDDM cube file with new transition
	    for (int ix=0;ix<Voxel_X;ix++) 
	    {
	      for (int iy=0;iy<Voxel_Y;iy++) 
	      {
		 for (int iz=0;iz<Voxel_Z;iz++) 
		 {
	  	 EDDM_Vector[ix][iy][iz]+= -Transition_Contribution*Occupied_Squared[ix][iy][iz]+Transition_Contribution*Virtual_Squared[ix][iy][iz]; 
		 }
	      }
	    } 	





return EDDM_Vector;
}
