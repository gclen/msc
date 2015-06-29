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


vector<double> Transition_Dipole_Moment(char Cube_File_Occupied[100], char Cube_File_Virtual[100])
{
        //Computes the transition dipole moment of two cube files

	struct Voxel_Info Voxel_Values;	
	int Voxel_X,Voxel_Y,Voxel_Z,Vector_Size,Index;
        double Dot_Prod_1,Dot_Prod_2,Dot_Prod_Norm,Trans_Dip,Trans_Dip_Total_Square;
        vector<double> Dist_to_Vox(3,0.0);
        vector<double> Trans_Dip_Vector(3,0.0);



	
        //Initialize variables
	Voxel_Values=Voxel_Read(Cube_File_Occupied);
	
	Voxel_X=Voxel_Values.Num_X;
	Voxel_Y=Voxel_Values.Num_Y;
	Voxel_Z=Voxel_Values.Num_Z;
    
        Index=0;
        
        Vector_Size=Voxel_X*Voxel_Y*Voxel_Z;  

 

        Dot_Prod_1=0;
        Dot_Prod_2=0; 
        Dot_Prod_Norm=0; 
        Trans_Dip=0;
        Trans_Dip_Total_Square=0;


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

        //Calculate the transition dipole moment 
        //That is the matrix element |<a|r|b>|
        while(Index<Vector_Size)
        {
                for(int i=0;i<Voxel_X;i++)
                {
                        for(int j=0;j<Voxel_Y;j++)
                        {
                                for(int k=0;k<Voxel_Z;k++)
                                {
                                Distance(i,j,k,Voxel_Values.Num_X,Voxel_Values.Num_Y,Voxel_Values.Num_Z,Voxel_Values.Vox_1_Step_X,Voxel_Values.Vox_1_Step_Y,Voxel_Values.Vox_1_Step_Z,Voxel_Values.Vox_2_Step_X,Voxel_Values.Vox_2_Step_Y,Voxel_Values.Vox_2_Step_Z, Voxel_Values.Vox_3_Step_X,Voxel_Values.Vox_3_Step_Y,Voxel_Values.Vox_3_Step_Z,Voxel_Values.X_0,Voxel_Values.Y_0,Voxel_Values.Z_0,Dist_to_Vox);

                                //X component of transition dipole moment
                                Trans_Dip_Vector[0]=Trans_Dip_Vector[0]+(Cube_Vector_1[Index]/(sqrt(Dot_Prod_1)))*Dist_to_Vox[0]*(Cube_Vector_2[Index]/(sqrt(Dot_Prod_2)));      
                                
                                //Y component of transition dipole moment
                                Trans_Dip_Vector[1]=Trans_Dip_Vector[1]+(Cube_Vector_1[Index]/(sqrt(Dot_Prod_1)))*Dist_to_Vox[1]*(Cube_Vector_2[Index]/(sqrt(Dot_Prod_2))); 

                                //Z component of transition dipole moment
                                Trans_Dip_Vector[2]=Trans_Dip_Vector[2]+(Cube_Vector_1[Index]/(sqrt(Dot_Prod_1)))*Dist_to_Vox[2]*(Cube_Vector_2[Index]/(sqrt(Dot_Prod_2))); 

                                //Increase index counter
                                Index++; 

                               //cout << "Index:\t" << i << "\t" << "Norm_cube_1\t" << (Cube_Vector_1[i]/(sqrt(Dot_Prod_1))) << "\t" << "Distance coordinates\t" << Dist_to_Vox[0] <<","<< Dist_to_Vox[1] <<","<< Dist_to_Vox[2] <<","<< "\t" << "Norm_cube_2\t" << (Cube_Vector_2[i]/(sqrt(Dot_Prod_2))) << "\t" << "Trans dipole vector:\t" << Trans_Dip_Vector[0]<< ","<< Trans_Dip_Vector[1]<< ","<< Trans_Dip_Vector[2]<< "," <<endl;
                                }
                        }
                } 
        }

        //Apply negative sign to each index
        for(int i=0;i<3;i++){
        Trans_Dip_Vector[i]=(-1.0)*Trans_Dip_Vector[i]; 
        }


return Trans_Dip_Vector;
}
