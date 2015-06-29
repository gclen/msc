#include <iostream>
#include <cmath>
#include <vector>
#include "Cube_Functions.h"

using namespace std;

vector<vector<vector<double> > > Square_Cubefile(int Voxel_X,int Voxel_Y,int Voxel_Z,vector<vector<vector<double> > >& VolumetricData)
{
	vector<vector<vector<double> > > VolumetricData_Squared;

	//Set up vector size
	VolumetricData_Squared.resize(Voxel_X);
	for(int i=0;i<Voxel_X;++i)
	{
	VolumetricData_Squared[i].resize(Voxel_Y);
	

		for(int j=0;j<Voxel_Y;++j)
		{
		VolumetricData_Squared[i][j].resize(Voxel_Z);
		}
	}

	for (int ix=0;ix<Voxel_X;ix++) 
	    {
	      for (int iy=0;iy<Voxel_Y;iy++) 
	      {
		 for (int iz=0;iz<Voxel_Z;iz++) 
		 {
	  	 VolumetricData_Squared[ix][iy][iz]=pow(VolumetricData[ix][iy][iz],2);
		 }
	      }
	    } 	


return VolumetricData_Squared;
}
