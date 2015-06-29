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
	char Coordinate_Input_File[20],Centered_Output_File[20];
	double x_coor[43],y_coor[43],z_coor[43],x_avg,y_avg,z_avg,Lattice_vector=25.0,x_tot=0.0,y_tot=0.0,z_tot=0.0;
	double x_centered[43],y_centered[43],z_centered[43];
	int Line_count=0;

	cout << "Please enter your xyz file (in direct coordinates)";
	cin >> Coordinate_Input_File;


	ifstream Coordinate_Input;
	Coordinate_Input.open(Coordinate_Input_File);
	ofstream Centered_Output;
	Centered_Output.open("Centered_Output_File");


	for (int i=0;i<44;i++){

		Coordinate_Input >> x_coor[i] >> y_coor[i] >> z_coor[i];



	}



	for (int i=0;i<44;i++){

	x_tot=x_tot+x_coor[i];
	y_tot=y_tot+y_coor[i];
	z_tot=z_tot+z_coor[i];

	}



	x_avg=x_tot/44.0;
	y_avg=y_tot/44.0;
	z_avg=z_tot/44.0;



	for (int i=0;i<44;i++){

	x_centered[i]=x_coor[i]-x_avg+Lattice_vector/2.0;
	y_centered[i]=y_coor[i]-y_avg+Lattice_vector/2.0;
	z_centered[i]=z_coor[i]-z_avg+Lattice_vector/2.0;

	}

	

	for (int i=0;i<44;i++){

	Centered_Output << x_centered[i] <<" "<< y_centered[i] <<" " << z_centered[i] <<endl;
	}







return 0;

}
