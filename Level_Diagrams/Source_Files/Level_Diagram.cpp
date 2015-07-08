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

#include "Level_Diagram_Functions.h"

using namespace std;


int main()
{
    string fchk_file,cube_name,log_name;
    string scaling_method="global";
    int Tot_occ_orb,Tot_virt_orb;
    struct Orbital_Struct Orb_Info;
    struct Voxel_Struct Voxel_Info;
    struct Global_Vals Bins_Max_Min;
    vector<double> wfn_data;
    vector<struct Bin_Struct> bin_data;
    vector<double> v;
    vector<double> point1;
    vector<double> point2;
    int num_bins;
    double point_coord=0.0;

    //Get the name of the output file to search
    cin >> log_name;
    //Get the name of the formatted checkpoint file
    cin >> fchk_file;
    //Get the number of occupied states required
    cin >> Tot_occ_orb;
    //Get the number of virtual states required 
    cin >> Tot_virt_orb;
    //Get the coordinates of the first point
    for (int i=0; i<3; i++)
    {
        cin >> point_coord;    
        point1.push_back(point_coord); 
    }
    //Get the coordinates of the second point
    for (int i=0; i<3; i++)
    {
        cin >> point_coord;
        point2.push_back(point_coord);
    }

    //Get the number of bins
    cin >> num_bins;
    //Get the method of scaling 
    cin >> scaling_method; 

    //Remove the previous output files
    system ("rm projected_sums.txt"); 
    system ("rm atom_projections.txt");

    Orb_Info=Energy_Read(log_name);
    Orb_Info=Get_Orbital_Numbers(Orb_Info,Tot_occ_orb,Tot_virt_orb);
    
    for (int i=0;i<Orb_Info.Orb_Nums_Vec.size();i++){
        cube_name=to_string(Orb_Info.Orb_Nums_Vec[i])+".cube";
        Cube_Generator(cube_name, fchk_file,Orb_Info.Orb_Nums_Vec[i]);
    }
    //Get the voxel info
    Voxel_Info=Voxel_Read(cube_name);
    //Find the equation of the line to project onto
    v=Find_Line_Equation(Voxel_Info, point1,point2); 

    //Project the atomic coordinates onto that line
    Project_Atom_Coords(Voxel_Info, v);


    if (scaling_method.compare("orbital")==0){
	    //Loop over all orbitals
	    for (int i=0;i<Orb_Info.Orb_Nums_Vec.size();i++){
	        //Get the name of the cube file 
	        cube_name=to_string(Orb_Info.Orb_Nums_Vec[i])+".cube";
	        
	        //Read in the data 
	        wfn_data=Cube_Read(cube_name, Voxel_Info);
	        //Project the points onto the line
	        bin_data=Project_Points(Voxel_Info, num_bins, v, wfn_data); 
	        
	     	bin_data = Orbital_Scale_Summed_Wfn(bin_data);    	

	        //Write out the data
	        if(i<Tot_occ_orb){
	            Write_Scaled_Sums(bin_data,Orb_Info.Occupied_Eng[Orb_Info.Occupied_Eng.size()-Tot_occ_orb+i]);
	        }
	        else {
	            Write_Scaled_Sums(bin_data,Orb_Info.Virtual_Eng[i-Tot_occ_orb]);
	        }
	        
	        wfn_data.clear();
	        bin_data.clear();
	    }
	}

    if (scaling_method.compare("global")==0){
	    //Loop over all orbitals to get global max and min
	    for (int i=0;i<Orb_Info.Orb_Nums_Vec.size();i++){
	        //Get the name of the cube file 
	        cube_name=to_string(Orb_Info.Orb_Nums_Vec[i])+".cube";
	        
	        //Read in the data 
	        wfn_data=Cube_Read(cube_name, Voxel_Info);
	        //Project the points onto the line
	        bin_data=Project_Points(Voxel_Info, num_bins, v, wfn_data); 

	        Bins_Max_Min=Global_Max_Min_Vals(bin_data,Bins_Max_Min);

	        wfn_data.clear();
	        bin_data.clear();

	    }
	    for (int j=0;j<Orb_Info.Orb_Nums_Vec.size();j++){
	        //Get the name of the cube file 
	        cube_name=to_string(Orb_Info.Orb_Nums_Vec[j])+".cube";
	        
	        //Read in the data 
	        wfn_data=Cube_Read(cube_name, Voxel_Info);
	        //Project the points onto the line
	        bin_data=Project_Points(Voxel_Info, num_bins, v, wfn_data); 

	        bin_data=Global_Scale_Summed_Wfn(bin_data,Bins_Max_Min);

	        //Write out the data
	        if(j<Tot_occ_orb){
	            Write_Scaled_Sums(bin_data,Orb_Info.Occupied_Eng[Orb_Info.Occupied_Eng.size()-Tot_occ_orb+j]);
	        }
	        else {
	            Write_Scaled_Sums(bin_data,Orb_Info.Virtual_Eng[j-Tot_occ_orb]);
	        }
	        
	        wfn_data.clear();
	        bin_data.clear();
	    }    
	}


return 0;
}






