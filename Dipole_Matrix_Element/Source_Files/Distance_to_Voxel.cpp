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


vector<double> Distance(int Vox_1_Count,int Vox_2_Count,int Vox_3_Count, int Num_X, int Num_Y, int Num_Z, double Vox_1_Step_X, double Vox_1_Step_Y, double Vox_1_Step_Z, double Vox_2_Step_X, double Vox_2_Step_Y, double Vox_2_Step_Z, double Vox_3_Step_X, double Vox_3_Step_Y, double Vox_3_Step_Z, double X_0, double Y_0, double Z_0, vector<double> & Dist_to_Vox) 
{

        //Computes the distance from the origin to a voxel
        double Voxel_Distance_Norm, X_dist, Y_dist,Z_dist;


        //Determine stepsize coefficients of voxel
/*        Vox_1_Count=floor(index/(Num_Z*Num_Y));
        Vox_2_Count=floor((index/(Num_Z))%Num_Y);
        Vox_3_Count=index%Num_Z;
*/

        //Compute length of vector in each direction
        //Add up stepsizes multiplied by their corresponding coefficient and subtract origin 
        
        //X coordinate
        Dist_to_Vox[0]=X_0+Vox_1_Count*Vox_1_Step_X+Vox_2_Count*Vox_2_Step_X+Vox_3_Count*Vox_3_Step_X;
        //Y coordinate
        Dist_to_Vox[1]=Y_0+Vox_1_Count*Vox_1_Step_Y+Vox_2_Count*Vox_2_Step_Y+Vox_3_Count*Vox_3_Step_Y;
        //Z coordinate
        Dist_to_Vox[2]=Z_0+Vox_1_Count*Vox_1_Step_Z+Vox_2_Count*Vox_2_Step_Z+Vox_3_Count*Vox_3_Step_Z;

        //Compute distance to voxel
        //Voxel_Distance_Norm=sqrt(pow(X_dist-X_0,2)+pow(Y_dist-Y_0,2)+pow(Z_dist-Z_0,2));

        //cout << Vox_1_Count << " " << Vox_2_Count << " " << Vox_3_Count << endl;



return Dist_to_Vox;
}
