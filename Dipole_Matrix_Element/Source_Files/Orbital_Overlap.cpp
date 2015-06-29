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


double Orbital_Overlap(char Cube_File_Occupied[100], char Cube_File_Virtual[100])
{
        //Computes the overlap of two cube files

	struct Voxel_Info Voxel_Values;	
	int Voxel_X,Voxel_Y,Voxel_Z,Vector_Size;
        double Dot_Prod_1,Dot_Prod_2,Dot_Prod_Norm,Vox_Dist,Overlap;


	
        //Initialize variables
	Voxel_Values=Voxel_Read(Cube_File_Occupied);
	
	Voxel_X=Voxel_Values.Num_X;
	Voxel_Y=Voxel_Values.Num_Y;
	Voxel_Z=Voxel_Values.Num_Z;
        
        Vector_Size=Voxel_X*Voxel_Y*Voxel_Z;  

 

        Dot_Prod_1=0;
        Dot_Prod_2=0; 
        Dot_Prod_Norm=0; 
        Vox_Dist=0; 
        Overlap=0;



	//Read in occupied cube file the first time   
	vector<vector<vector<double> > > VolumetricData1=Cube_Read(Cube_File_Occupied);
        
        //Read in a second time
        vector<vector<vector<double> > > VolumetricData2=Cube_Read(Cube_File_Virtual);
	
	//Convert from 3D vector to 1D vector with same ordering
        //It is done twice for computation of the dot product 
	vector<double> Cube_Vector_1=Cube_To_Vector(Cube_File_Occupied,VolumetricData1);
        vector<double> Cube_Vector_2=Cube_To_Vector(Cube_File_Virtual,VolumetricData2);
        
        //Find the normalization factor
        for(int i=0;i<Vector_Size;i++)
        {
        Dot_Prod_1+=Cube_Vector_1[i]*Cube_Vector_1[i];
        Dot_Prod_2+=Cube_Vector_2[i]*Cube_Vector_2[i];

        }



        //cout << "Dot_prod_1 " << Dot_Prod_1 << " " << "Dot_prod_2 " << Dot_Prod_2 << endl; 

        //Calculate the overlap between 2 orbitals 
        //That is the matrix element <a|r|b>
        for(int i=0;i<Vector_Size;i++)
        {

        Overlap+=(Cube_Vector_1[i]/(sqrt(Dot_Prod_1)))*(Cube_Vector_2[i]/(sqrt(Dot_Prod_2)));      

        }

        


return Overlap;
}
