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

vector<struct Bin_Struct> Project_Points(Voxel_Struct &Voxel_Info, int tot_bin_num,vector<double> v_vec, vector<double> wfn_array)
{
    double mag_v,dv,bin_key,proj_u_on_v;
    int index=0;

    //Store the bins in a vector
    //Each bin will be an instance of the bin struct
    vector<Bin_Struct> projection_bins(tot_bin_num);

    //Get the magnitude of the vector
    for (int i=0; i<v_vec.size();i++){
        mag_v+=pow(v_vec[i],2);
    }
    mag_v=sqrt(mag_v);    

    //Find the bin size 
    dv=mag_v/tot_bin_num;

    //Populate the distance to the bin in Angstroms
    for (int i=0;i<tot_bin_num;i++){
        projection_bins[i].dist_to_bin=i*dv*0.529177249;
    }

    //Loop over the wfn array and project onto v_vec
    for (int i=0; i< Voxel_Info.Num_X;i++){
        for (int j=0; j<Voxel_Info.Num_Y;j++){
            for (int k=0; k<Voxel_Info.Num_Z; k++){
                //Get the distance projection
                proj_u_on_v=(i*Voxel_Info.Vox_1_Step_X*v_vec[0]+j*Voxel_Info.Vox_2_Step_Y*v_vec[1]+k*Voxel_Info.Vox_3_Step_Z*v_vec[2])/mag_v;
                if (proj_u_on_v>mag_v){
                    cout << "Error: projection is bigger than the vector" << endl;
                }
                //Find which bin it should go in
                bin_key=round(proj_u_on_v/dv);
                //If it is the same as the number of bins subtract one since the 
                //indexing starts at 0
                if (bin_key==tot_bin_num){
                    bin_key-=1;
                }
                //Add psi squared to the appropriate value
                projection_bins[bin_key].wfn_sq_sum+=pow(wfn_array[index],2);
                //Increase the bin counter
                projection_bins[bin_key].point_count+=1;
                
                index+=1;
                
                }
            }
        }
        


return projection_bins;
}
