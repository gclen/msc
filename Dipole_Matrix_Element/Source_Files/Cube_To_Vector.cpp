#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "Cube_Functions.h"

using namespace std;

vector<double> Cube_To_Vector(char Cube_File_Occupied[50],vector<vector<vector<double> > >& VolumetricData)
{

        //Takes a 3D cube file and puts it into a 1D vector
	vector<double> Cube_Vector;
        int Vector_Size,Vector_Index,Voxel_X,Voxel_Y,Voxel_Z;
	struct Voxel_Info Voxel_Values;	

        //Initialize variables
	Voxel_Values=Voxel_Read(Cube_File_Occupied);
	
	Voxel_X=Voxel_Values.Num_X;
	Voxel_Y=Voxel_Values.Num_Y;
	Voxel_Z=Voxel_Values.Num_Z;
        Vector_Size=Voxel_X*Voxel_Y*Voxel_Z;
  
        Vector_Index=0;  

	//Set up vector size
	Cube_Vector.resize(Vector_Size);

	for (int ix=0;ix<Voxel_X;ix++) 
	    {
	      for (int iy=0;iy<Voxel_Y;iy++) 
	      {
		 for (int iz=0;iz<Voxel_Z;iz++) 
		 {
	  	 Cube_Vector[Vector_Index]=VolumetricData[ix][iy][iz];
                 
                 //cout << Vector_Index << " " << Cube_Vector[Vector_Index] <<endl;
                 Vector_Index++;
                 
		 }
	      }
	    } 	


return Cube_Vector;
}
