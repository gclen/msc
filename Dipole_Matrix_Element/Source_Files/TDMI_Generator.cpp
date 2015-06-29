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


int main()
{

	char Cube_File_Occupied[100], Cube_File_Virtual[100];
        double Trans_Dip_Norm=0;
        vector<double> Cube_Vector;
        vector<double> Trans_Dip_Vector;

	//Get filenames from keyboard input
	cout << "Please enter occupied orbital: ";
	cin >> Cube_File_Occupied;

	cout << "Please enter unoccupied orbital: ";
	cin >> Cube_File_Virtual;
        
        cout <<endl;


        Trans_Dip_Vector=Transition_Dipole_Moment(Cube_File_Occupied,Cube_File_Virtual);
        Trans_Dip_Norm=sqrt(pow(Trans_Dip_Vector[0],2)+pow(Trans_Dip_Vector[1],2)+pow(Trans_Dip_Vector[2],2)); 
        
        cout << "The transition dipole moment (x,y,z) is: " << Trans_Dip_Vector[0] <<"," <<Trans_Dip_Vector[1] <<"," << Trans_Dip_Vector[2] <<  endl;
        cout << "The norm is: " << Trans_Dip_Norm << endl;
 



return 0;
}
