#ifndef __CUBE_READ_H_
#define __CUBE_READ_H_

using namespace std;

void Cube_Generator(string Cube_File_Name,string fchk_name, int orb_num);
struct Orbital_Struct Energy_Read(string G09_output_file);
bool File_Exists(string Test_File);
struct Orbital_Struct Get_Orbital_Numbers(Orbital_Struct &Orb_Info, int Num_Occ, int Num_Virt);
struct Voxel_Struct Voxel_Read(string Cube_File_Name);
vector<double> Cube_Read(string Cube_File_Name, Voxel_Struct &Voxel_Info);
vector<double> Find_Line_Equation(Voxel_Struct &Voxel_Info, vector<double> P1, vector<double> P2);
vector<struct Bin_Struct> Project_Points(Voxel_Struct &Voxel_Info, int tot_bin_num, vector<double> v_vec, vector<double> wfn_array);
vector<struct Bin_Struct> Orbital_Scale_Summed_Wfn(vector <struct Bin_Struct> &projection_bins);
vector<struct Bin_Struct> Global_Scale_Summed_Wfn(vector <struct Bin_Struct> &projection_bins, struct Global_Vals &bins_max_min);
struct Global_Vals Global_Max_Min_Vals(vector <struct Bin_Struct> &projection_bins, struct Global_Vals &bins_max_min);
void Write_Scaled_Sums(vector <struct Bin_Struct> &bin_data, double Energy);
void Project_Atom_Coords(Voxel_Struct &Voxel_Info, vector<double> v_vec);

struct Orbital_Struct
    {
        vector<double> Occupied_Eng;
        vector<double> Virtual_Eng;
        vector<int> Orb_Nums_Vec;
    };

struct Voxel_Struct
    {
        int Num_X;
        int Num_Y;
        int Num_Z;
        int Num_Atoms;
        double Vox_1_Step_X;
        double Vox_1_Step_Y;
        double Vox_1_Step_Z;
        double Vox_2_Step_X;
        double Vox_2_Step_Y;
        double Vox_2_Step_Z;
        double Vox_3_Step_X;
        double Vox_3_Step_Y;
        double Vox_3_Step_Z;
        double X_0;
        double Y_0;
        double Z_0;
        vector<vector <double>> Coord_List;     
    };

struct Bin_Struct
    {
        double wfn_sq_sum=0.0;
        double point_count=0.0;
        double dist_to_bin;
        double scaled_sum;
    };

struct Global_Vals
    {
        double glob_min_sum=(-1.0);
        double glob_max_sum=(-1.0);
    };


#endif
