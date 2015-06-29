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

vector<double> Cube_Read(string Cube_File_Name, Voxel_Struct &Voxel_Info)
{
    int Num_Atoms_Temp;
    vector<double> wfn_array;
    double psi_temp;

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

    //Ignore header
    for (int i=0;i<(7+Voxel_Info.Num_Atoms);i++){
        CubeInput.ignore(256,'\n' ); 
    }
    
    for (int i=0;i<Voxel_Info.Num_X;i++){
        for (int j=0; j< Voxel_Info.Num_Y; j++){
            for (int k=0; k < Voxel_Info.Num_Z; k++){
                CubeInput >> psi_temp;
                wfn_array.push_back(psi_temp);
            }
        }
    }

CubeInput.close();


return wfn_array;
}
