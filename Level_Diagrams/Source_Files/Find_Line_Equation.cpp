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

vector<double> Find_Line_Equation(Voxel_Struct &Voxel_Info, vector<double> P1, vector<double> P2) 
{
    int min_dist_index;
    double x_size,y_size,z_size,t_max,t_xmax,t_ymax,t_zmax,max_dist,min_dist,t_min,t_xmin,t_ymin,t_zmin;
    double cell_diag,mag_line=0;
    vector<double> dir_vec;
    vector<double> t_max_vals;
    vector<double> t_min_vals;
    vector<double> max_dist_list;
    vector<double> min_dist_list;
    vector<double> max_point;
    vector<double> min_point;
    vector<double> line;
    vector<double> unit_line;
    vector<double> scaled_vec;

    //Get the box size in the x direction which is num_X*step_X
    x_size=Voxel_Info.Num_X*Voxel_Info.Vox_1_Step_X;
    //Get the box size in the y direction which is num_Y*step_Y
    y_size=Voxel_Info.Num_Y*Voxel_Info.Vox_2_Step_Y;
    //Get the box size in the x direction which is num_X*step_X
    z_size=Voxel_Info.Num_Z*Voxel_Info.Vox_3_Step_Z;

    //Put the points in the voxel coordinate system
    //Subtract the origin from each point
    P1[0]+=Voxel_Info.X_0;
    P1[1]+=Voxel_Info.Y_0;
    P1[2]+=Voxel_Info.Z_0; 

    P2[0]+=Voxel_Info.X_0;
    P2[1]+=Voxel_Info.Y_0;
    P2[2]+=Voxel_Info.Z_0;

    //Find the vector connecting the two points
    //Call it <a,b,c>
    dir_vec={P2[0]-P1[0],P2[1]-P1[1],P2[2]-P1[2]};
    
    /*
    This means the parametric equations of the line are 
    x(t)=x0+at
    y(t)=y0+bt
    z(t)=z0+ct

    Want to solve for t's that correspond to the edges of the box 
    For example the t corresponding to the far x boundary will be
    t=(x_size-x0)/a
    */

    //If x0 or y0 or z0 is the boundary of the box then just take that point
    if (P1[0]==x_size || P1[1]==y_size || P1[2]==z_size){
        t_max=0;
    }
    //Else solve for t
    else{
        if (dir_vec[0]!=0){
            t_xmax=(x_size-P1[0])/(dir_vec[0]);
            t_max_vals.push_back(t_xmax);     
        }
        if (dir_vec[1]!=0){
            t_ymax=(y_size-P1[1])/(dir_vec[1]);
            t_max_vals.push_back(t_ymax);
        }
        if (dir_vec[2]!=0){
            t_zmax=(z_size-P1[2])/(dir_vec[2]);
            t_max_vals.push_back(t_zmax);
        }
    
        //Compute the distance and take the minimum. The t corresponding to this
        //is the one that we want to use for all equations
        for (int i=0; i<t_max_vals.size(); i++){
            max_dist=sqrt(pow(dir_vec[0]*t_max_vals[i],2)+pow(dir_vec[1]*t_max_vals[i],2)+pow(dir_vec[2]*t_max_vals[i],2));
            max_dist_list.push_back(max_dist);
        }
        
        //Get the t corresponding to that distance 
        min_dist_index=distance(max_dist_list.begin(),min_element(max_dist_list.begin(),max_dist_list.end()));
        t_max=t_max_vals[min_dist_index];       
   
        //Thus the point on the box face that is on the line is 
        //(x0+a*tmax,y0+b*tmax,z0+c*tmax)
        max_point={P1[0]+t_max*dir_vec[0],P1[1]+t_max*dir_vec[1],P1[2]+t_max*dir_vec[2]};
    }   
    
    //If x0 or y0 or z0 is the boundary of the box then just take that point
    if (P1[0]==0.0 || P1[1]==0.0 || P1[2]==0.0){
        t_min=0;
    }
    //Else solve for t
    else{
        if (dir_vec[0]!=0){
            t_xmin=(0.0-P1[0])/(dir_vec[0]);
            t_min_vals.push_back(t_xmin);
        }
        if (dir_vec[1]!=0){
            t_ymin=(0.0-P1[1])/(dir_vec[1]);
            t_min_vals.push_back(t_ymin);
        }
        if (dir_vec[2]!=0){
            t_zmin=(0.0-P1[2])/(dir_vec[2]);
            t_min_vals.push_back(t_zmin);
        }

        //Compute the distance and take the minimum. The t corresponding to this
        //is the one that we want to use for all equations
        for (int i=0; i<t_min_vals.size(); i++){
            min_dist=sqrt(pow(dir_vec[0]*t_min_vals[i],2)+pow(dir_vec[1]*t_min_vals[i],2)+pow(dir_vec[2]*t_min_vals[i],2));
            min_dist_list.push_back(min_dist);
        }

        //Get the t corresponding to that distance 
        min_dist_index=distance(min_dist_list.begin(),min_element(min_dist_list.begin(),min_dist_list.end()));
        t_min=t_min_vals[min_dist_index];
    
        //Thus the point on the box face that is on the line is 
        //(x0+a*tmin,y0+b*tmin,z0+c*tmin)
        min_point={P1[0]+t_min*dir_vec[0],P1[1]+t_min*dir_vec[1],P1[2]+t_min*dir_vec[2]};
    }

    //The line we want contains the min point and max point
    line={max_point[0]-min_point[0],max_point[1]-min_point[1],max_point[2]-min_point[2]};
    
    //We want it to be the same length as the cell diagonal
    //The cell diagonal is
    cell_diag=sqrt(pow(x_size,2)+pow(y_size,2)+pow(z_size,2));
    
    //Get the magnitude
    for (int i=0; i<line.size();i++){
        mag_line+=pow(line[i],2);
    }
    mag_line=sqrt(mag_line);
    
    //Get the unit vector of our line
    for (int i=0;i<line.size();i++){
        unit_line.push_back(line[i]/mag_line);
    }
    
    //Multiply by the length of the cell diagonal
    for (int i=0;i<unit_line.size();i++){
        scaled_vec.push_back(unit_line[i]*cell_diag);
    }

return scaled_vec;
}
