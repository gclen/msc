#ifndef __CUBE_READ_H_
#define __CUBE_READ_H_

using namespace std;

vector<vector<vector<double> > > Cube_Read(char Cube_File_Name[100]);
void Cube_Header(char Cube_File_Name[100]);
void Cube_Write(int Num_X, int Num_Y, int Num_Z,vector<vector<vector<double> > >& TDMI_Vector);
vector<vector<vector<double> > > Transition(char Cube_File_Occupied[100], char Cube_File_Virtual[50],double Transition_Contribution,vector<vector<vector<double> > >& TDMI_Vector);
vector<vector<vector<double> > > Square_Cubefile(int Voxel_X,int Voxel_Y,int Voxel_Z,vector<vector<vector<double> > >& VolumetricData);
vector<vector<vector<double> > > TDMI_Vector_Initialize(char Cube_File_Occupied[100]);
struct Voxel_Info Voxel_Read(char Cube_File_Name[100]); 
void Cube_Generator(int Orbital_Number,bool isAlpha,char Checkpoint_File_Name[50]);
double Cube_Norm(char Cube_File_Occupied[100]);
vector<double> Cube_To_Vector(char Cube_File_Occupied[100],vector<vector<vector<double> > >& VolumetricData);
double Cube_Dot_Product(char Cube_File_Occupied[100],char Cube_File_Virtual[100]);
vector<double> Distance(int Vox_1_Count,int Vox_2_Count,int Vox_3_Count, int Num_X, int Num_Y, int Num_Z, double Vox_1_Step_X, double Vox_1_Step_Y, double Vox_1_Step_Z, double Vox_2_Step_X, double Vox_2_Step_Y, double Vox_2_Step_Z, double Vox_3_Step_X, double Vox_3_Step_Y, double Vox_3_Step_Z, double X_0, double Y_0, double Z_0, vector<double> & Dist_to_Vox); 
vector<double> Transition_Dipole_Moment(char Cube_File_Occupied[100], char Cube_File_Virtual[100]);
double Orbital_Overlap(char Cube_File_Occupied[100], char Cube_File_Virtual[100]);

struct Voxel_Info 
	{
		int Num_X;
		int Num_Y;
		int Num_Z;
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

	};

#endif
