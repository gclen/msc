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
void Cube_Header(char Cube_File_Name[50])
{

// Read in cube file

	int Num_Atoms,Num_Atoms_Temp,Num_X=0, Num_Y=0, Num_Z=0,Header_Lines;
	char Header_Buffer[256];

	//Input from file
	ifstream CubeInput;
	CubeInput.open(Cube_File_Name);

    //Temp output
    ofstream CubeOutput;
    CubeOutput.open("TDMI_Output.cube", ios::app);
  
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

        //Read in number of atoms 
	CubeInput >> Num_Atoms_Temp;
	CubeInput.ignore(80, '\n' );

        //Number of atoms is listed as a negative number
        Num_Atoms=abs(Num_Atoms_Temp);

        //Read in number of iterations in each direction
	CubeInput >> Num_X;
	CubeInput.ignore(80, '\n' );
	CubeInput >> Num_Y;
	CubeInput.ignore(80, '\n' );
	CubeInput >> Num_Z;
	CubeInput.ignore(80, '\n' );

        	for(int Atom=0;Atom<=Num_Atoms;Atom++)
		{
        	CubeInput.ignore(80, '\n' );
		}

CubeInput.close();

	//Open cubefile again and print header to output file


	//Input from file
	ifstream CubeHeader;
	CubeHeader.open(Cube_File_Name);

	//Header will have 2 comment lines, 1 line for the center positon, 3 lines for voxel definitions and one after the atomic coordinates
	//There is one line for each atom as well
	Header_Lines=Num_Atoms+7;

	for(int i=0;i<Header_Lines;i++)
	{
	CubeHeader.getline(Header_Buffer, 256);
	CubeOutput << Header_Buffer << endl;
	}

CubeInput.close();


return;
}
