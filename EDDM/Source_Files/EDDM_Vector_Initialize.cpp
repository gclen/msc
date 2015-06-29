#include <iostream>
#include <cmath>
#include <vector>
#include "Cube_Functions.h"

using namespace std;

vector<vector<vector<double> > > EDDM_Vector_Initialize(char Cube_File_Occupied[50])
{
	struct Voxel_Info Voxel_Values;	
	int Voxel_X,Voxel_Y,Voxel_Z;
	vector<vector<vector<double> > > EDDM_Vector;
	

	Voxel_Values=Voxel_Read(Cube_File_Occupied);
	
	Voxel_X=Voxel_Values.Num_X;
	Voxel_Y=Voxel_Values.Num_Y;
	Voxel_Z=Voxel_Values.Num_Z;

	//Set up vector size
	EDDM_Vector.resize(Voxel_X);
	for(int i=0;i<Voxel_X;++i)
	{
	EDDM_Vector[i].resize(Voxel_Y);
	

		for(int j=0;j<Voxel_Y;++j)
		{
		EDDM_Vector[i][j].resize(Voxel_Z);
		}
	}

	for (int ix=0;ix<Voxel_X;ix++) 
	    {
	      for (int iy=0;iy<Voxel_Y;iy++) 
	      {
		 for (int iz=0;iz<Voxel_Z;iz++) 
		 {
	  	 EDDM_Vector[ix][iy][iz]=0.0;
         }
	      }
	    } 	


return EDDM_Vector;
}
