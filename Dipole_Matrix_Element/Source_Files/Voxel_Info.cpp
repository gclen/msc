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

struct Voxel_Info Voxel_Read(char Cube_File_Name[50])
{
	struct Voxel_Info Voxel_Numbers;
	int Num_Atoms,Num_Atoms_Temp,Num_X=0, Num_Y=0, Num_Z=0,Header_Lines;
	char Header_Buffer[256];

	//Input from file
	ifstream CubeInput;
	CubeInput.open(Cube_File_Name);

 
	//Test file is good 
        while(CubeInput.good()== false)
        {
        cout << "Unable to open cube file. Enter a new name: ";
        cin >> Cube_File_Name;
        // Clear the file stream
        CubeInput.clear();
        CubeInput.open(Cube_File_Name);
        }


        //Parse header for system information
        //Ignore first 2 lines
        CubeInput.ignore(80,'\n' );	
        CubeInput.ignore(80, '\n' );	

        //Read in number of atoms and origin
	CubeInput >> Num_Atoms_Temp;
	CubeInput >> Voxel_Numbers.X_0;
	CubeInput >> Voxel_Numbers.Y_0;
	CubeInput >> Voxel_Numbers.Z_0;


        //Read in number of voxels and step sizes in each direction
	CubeInput >> Voxel_Numbers.Num_X;
	CubeInput >> Voxel_Numbers.Vox_1_Step_X;
	CubeInput >> Voxel_Numbers.Vox_1_Step_Y;
	CubeInput >> Voxel_Numbers.Vox_1_Step_Z;
	CubeInput >> Voxel_Numbers.Num_Y;
	CubeInput >> Voxel_Numbers.Vox_2_Step_X;
	CubeInput >> Voxel_Numbers.Vox_2_Step_Y;
	CubeInput >> Voxel_Numbers.Vox_2_Step_Z;
	CubeInput >> Voxel_Numbers.Num_Z;
	CubeInput >> Voxel_Numbers.Vox_3_Step_X;
	CubeInput >> Voxel_Numbers.Vox_3_Step_Y;
	CubeInput >> Voxel_Numbers.Vox_3_Step_Z;



CubeInput.close();


return Voxel_Numbers;
}
