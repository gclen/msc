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
#include <string>
#include <algorithm>

#include "Level_Diagram_Functions.h"

using namespace std;

void Project_Atom_Coords(Voxel_Struct &Voxel_Info, vector<double> v_vec)
{
    double mag_v,dv,proj_u_on_v;
    int index=0;

    ofstream Data_write; 
    Data_write.open("atom_projections.txt",ios::app);

    //Get the magnitude of the vector
    for (int i=0; i<v_vec.size();i++){
        mag_v+=pow(v_vec[i],2);
    }
    mag_v=sqrt(mag_v);    

    for(int i=0;i<Voxel_Info.Coord_List.size();i++){
        //Project and convert to angstroms     
        proj_u_on_v=(((Voxel_Info.Coord_List[i][0]-(Voxel_Info.X_0))*v_vec[0]
                     +(Voxel_Info.Coord_List[i][1]-(Voxel_Info.Y_0))*v_vec[1]
                     +(Voxel_Info.Coord_List[i][2]-(Voxel_Info.Z_0))*v_vec[2])/mag_v)*0.529177249;
        
        if (proj_u_on_v>mag_v){
            cout << "Error: projection is bigger than the vector" << endl;
        }       
        
        Data_write << i << " " << proj_u_on_v << endl;   
    }

return;
}