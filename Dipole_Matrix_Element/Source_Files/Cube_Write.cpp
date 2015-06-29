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

#include "Cube_Functions.h"

using namespace std;
void Cube_Write(int Num_X, int Num_Y, int Num_Z,vector<vector<vector<double> > >& TDMI_Vector)
{

int Column_Count=0;

    //Initialize output stream
    ofstream CubeOutput;
    CubeOutput.open("TDMI_Output.cube", ios::app);

	    //Set precision
	    CubeOutput << setiosflags(ios::scientific)<< setprecision(5) << " ";

	    //Write data to file
	    for (int ix=0;ix<Num_X;ix++) 
	    {
	      for (int iy=0;iy<Num_Y;iy++) 
	      {
		 for (int iz=0;iz<Num_Z;iz++) 
		 {
		 CubeOutput <<TDMI_Vector[ix][iy][iz]<< setw(14);
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
