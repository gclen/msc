#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <complex>
#include <vector>
#include <iomanip>
#include <string>

#include "Level_Diagram_Functions.h"

using namespace std;

struct Voxel_Struct Voxel_Read(string Cube_File_Name)
{
    struct Voxel_Struct Voxel_Info;
    int Num_Atoms_Temp;
    double atom_type, atom_charge, coord_x, coord_y, coord_z;
    vector<double> coord_temp;

    //Input from file
    ifstream CubeInput;
    CubeInput.open(Cube_File_Name.c_str());

 
    //Test file is good 
    while(CubeInput.good()== false)
    {
    cout << "Unable to open cube file. Enter a new name: ";
    cin >> Cube_File_Name;
    // Clear the file stream
    CubeInput.clear();
    CubeInput.open(Cube_File_Name.c_str());
    }


    //Parse header for system information
    //Ignore first 2 lines
    CubeInput.ignore(80,'\n' ); 
    CubeInput.ignore(80, '\n' );    

    //Read in number of atoms and origin
    CubeInput >> Num_Atoms_Temp;
    Voxel_Info.Num_Atoms=abs(Num_Atoms_Temp);
    
    CubeInput >> Voxel_Info.X_0;
    CubeInput >> Voxel_Info.Y_0;
    CubeInput >> Voxel_Info.Z_0;


    //Read in number of voxels and step sizes in each direction
    CubeInput >> Voxel_Info.Num_X;
    CubeInput >> Voxel_Info.Vox_1_Step_X;
    CubeInput >> Voxel_Info.Vox_1_Step_Y;
    CubeInput >> Voxel_Info.Vox_1_Step_Z;
    CubeInput >> Voxel_Info.Num_Y;
    CubeInput >> Voxel_Info.Vox_2_Step_X;
    CubeInput >> Voxel_Info.Vox_2_Step_Y;
    CubeInput >> Voxel_Info.Vox_2_Step_Z;
    CubeInput >> Voxel_Info.Num_Z;
    CubeInput >> Voxel_Info.Vox_3_Step_X;
    CubeInput >> Voxel_Info.Vox_3_Step_Y;
    CubeInput >> Voxel_Info.Vox_3_Step_Z;


    //Get the atomic coordinates 
    for (int i=0;i<Voxel_Info.Num_Atoms;i++){
        //Read in the line
        CubeInput >> atom_type;
        CubeInput >> atom_charge;
        CubeInput >> coord_x;
        CubeInput >> coord_y;
        CubeInput >> coord_z;
        //Put the coordinates in a temporary vector
        coord_temp.push_back(coord_x);
        coord_temp.push_back(coord_y);
        coord_temp.push_back(coord_z);
        //Add to the struct
        Voxel_Info.Coord_List.push_back(coord_temp);
        //Clear the temp list
        coord_temp.clear();

    }

CubeInput.close();


return Voxel_Info;
}
