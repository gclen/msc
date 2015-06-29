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

int main()
{

	char Cube_File_Occupied[50], Cube_File_Virtual[50],EDDM_Output_File[50];
	double Transition_Contribution;
    //vector<vector<vector<double> > > EDDM_Vector;

    //Get filenames from keyboard input
	//cout << "Please enter occupied orbital: ";
	cin >> Cube_File_Occupied;

	//cout << "Please enter unoccupied orbital: ";
	cin >> Cube_File_Virtual;

    //cout << "Please enter output cubefile name: ";
    cin >> EDDM_Output_File;
    
    cin >> Transition_Contribution;
    
    //Check if the EDDM output file exists 
    //If it does then read in its values into the EDDM_Vector
    if (File_Exists(EDDM_Output_File)==true) {
        //Initialize EDDM vector with previous values
        vector<vector<vector<double> > > EDDM_Vector=Cube_Read(EDDM_Output_File); 
        //Update EDDM vector with transition
        Transition(Cube_File_Occupied,Cube_File_Virtual,Transition_Contribution,EDDM_Vector);
        //Write the updated vector to a cube file 
        Cube_Write(Cube_File_Occupied,EDDM_Vector,EDDM_Output_File);

    }
    else{
	    //Initialize EDDM vector with zeros
	    vector<vector<vector<double> > > EDDM_Vector=EDDM_Vector_Initialize(Cube_File_Occupied);
	    //Update EDDM vector with transition
        Transition(Cube_File_Occupied,Cube_File_Virtual,Transition_Contribution,EDDM_Vector);
        //Write the updated vector to a cube file 
        Cube_Write(Cube_File_Occupied,EDDM_Vector,EDDM_Output_File);
    }
   
    /*
    //Update EDDM vector with transition
	Transition(Cube_File_Occupied,Cube_File_Virtual,Transition_Contribution,EDDM_Vector);
	
    Cube_Write(Cube_File_Occupied,EDDM_Vector,EDDM_Output_File);
    */


return 0;
}
