#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iomanip>

#include "Cube_Functions.h"

using namespace std;
void Cube_Write(char Cube_File_Occupied[50], vector<vector<vector<double> > >& EDDM_Vector, char EDDM_Output_File[50])
{

struct Voxel_Info Voxel_Values;
int Column_Count=0,Num_Atoms,Header_Lines,Num_X,Num_Y,Num_Z;
char Header_Buffer[256];

    Voxel_Values=Voxel_Read(Cube_File_Occupied);

    //Get the values for the number of voxels in each direction
    Num_X=Voxel_Values.Num_X;
    Num_Y=Voxel_Values.Num_Y;
    Num_Z=Voxel_Values.Num_Z;

    //Initialize input stream of occupied file to get the header info
    //Input from file
    ifstream CubeHeader;
    CubeHeader.open(Cube_File_Occupied);
    
    //Initialize output stream
    ofstream CubeOutput;
    CubeOutput.open(EDDM_Output_File);

    //Write out the header
    Num_Atoms=Voxel_Values.Num_Atoms;
    
    
    //Header will have 2 comment lines, 1 line for the center positon, 3 lines for voxel definitions and one after the atomic coordinates
    //There is one line for each atom as well
    Header_Lines=Num_Atoms+7;

    for(int i=0;i<Header_Lines;i++)
    {
    CubeHeader.getline(Header_Buffer, 256);
    CubeOutput << Header_Buffer << endl;
    }
    
    //Close the input file stream
    CubeHeader.close();

    //Set precision
    CubeOutput << setiosflags(ios::scientific)<< setprecision(5) << " ";

    //Write data to file
    for (int ix=0;ix<Num_X;ix++) 
    {
        for (int iy=0;iy<Num_Y;iy++) 
        {
            for (int iz=0;iz<Num_Z;iz++) 
            {
                CubeOutput <<EDDM_Vector[ix][iy][iz]<< setw(14);
                Column_Count=Column_Count+1;
        
                if(Column_Count==6)
                {
                CubeOutput << "\n" << " ";
                Column_Count=0;
                }
                
                if(iz==Num_Z-1)
                {
                CubeOutput << "\n" << " ";
                }
                    
            }
            Column_Count=0;
        }
    } 

CubeOutput.close();
 
return;
}
