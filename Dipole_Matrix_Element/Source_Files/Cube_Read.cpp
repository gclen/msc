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
vector<vector<vector<double> > > Cube_Read(char Cube_File_Name[50])
{

// Read in cube file to array

	int Num_Atoms,Num_Atoms_Temp,Num_X=0, Num_Y=0, Num_Z=0,Col_Num;
	vector<vector<vector<double> > > Coordinate;

	//Input from file
	ifstream CubeInput;
	CubeInput.open(Cube_File_Name);

    
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

        //Number of atoms is listed as a negative number so the absolute value is taken
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

	//Set up vector size
	Coordinate.resize(Num_X);
	for(int i=0;i<Num_X;++i)
	{
	Coordinate[i].resize(Num_Y);
	

		for(int j=0;j<Num_Y;++j)
		{
		Coordinate[i][j].resize(Num_Z);
		}
	}
	    // Find number of columns on last line of block
            Col_Num=Num_Z%6;

	    //Read in volumetric data

	    for (int ix=0;ix<Num_X;ix++) 
	    {
	      for (int iy=0;iy<Num_Y;iy++) 
	      {
		 for (int iz=0;iz<Num_Z;iz++) 
		 {
	  	 CubeInput >> Coordinate[ix][iy][iz]; 
		 }
	      }
	    } 

CubeInput.close();


return Coordinate;
}
