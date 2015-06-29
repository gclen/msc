#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;
int main()
{

// Read in cube file to array

	const int Buff_Size=100;
	int Num_Atoms,Num_Atoms_Temp,Num_X=0, Num_Y=0, Num_Z=0,Col_Num;
	char Cube_File_Name[50],Data_Buffer[Buff_Size];
	long double Coordinate[79][79][82];

	//Get filename from keyboard input
	cout << "Please enter cube file name: ";
	cin >> Cube_File_Name;

	//Input from file
	ifstream CubeInput;
	CubeInput.open(Cube_File_Name);

    //Temp output
    ofstream CubeOutput;
    CubeOutput.open("CubeDump.txt", ios::app);
   
    
        while(CubeInput.good()== false)
        {
        cout << "Unable to open cube file. Enter a new name: ";
        cin >> Cube_File_Name;
        // Clear the file stream
        CubeInput.clear();
        CubeInput.open(Cube_File_Name);
        }

        //Parse header for system information
/*        
	// Put a full line of input into the buffer
        CubeInput.getline(Data_Buffer, Buff_Size);

        // Copy the line into the string stream    
        Cube_Stream << Data_Buffer; 
*/
   //     ws(CubeInput);  

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

	    for (int ix=0;ix<Num_X;ix++) 
	    {
	      for (int iy=0;iy<Num_Y;iy++) 
	      {
		 for (int iz=0;iz<Num_Z;iz++) 
		 {
		 CubeOutput<< ix << " " << iy << " " << iz << " " << Coordinate[ix][iy][iz] <<endl;
		 }
	      }
	    } 

CubeInput.close();

cout << Num_Atoms << " " << Num_X << " " << Num_Y << " " << Num_Z << endl;    


    


return 0;
}
