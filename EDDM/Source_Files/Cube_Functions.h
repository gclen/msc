#ifndef __CUBE_READ_H_
#define __CUBE_READ_H_

using namespace std;

vector<vector<vector<double> > > Cube_Read(char Cube_File_Name[50]);
void Cube_Header(char Cube_File_Name[50]);
void Cube_Write(char Cube_File_Occupied[50], vector<vector<vector<double> > >& EDDM_Vector, char EDDM_Output_File[50]);
vector<vector<vector<double> > > Transition(char Cube_File_Occupied[50], char Cube_File_Virtual[50],double Transition_Contribution,vector<vector<vector<double> > >& EDDM_Vector);
vector<vector<vector<double> > > Square_Cubefile(int Voxel_X,int Voxel_Y,int Voxel_Z,vector<vector<vector<double> > >& VolumetricData);
vector<vector<vector<double> > > EDDM_Vector_Initialize(char Cube_File_Occupied[50]);
struct Voxel_Info Voxel_Read(char Cube_File_Name[50]); 
void Cube_Generator(int Orbital_Number,bool isAlpha,char Checkpoint_File_Name[50]);
bool File_Exists(char Test_File[50]);

struct Voxel_Info 
	{
		int Num_X;
		int Num_Y;
		int Num_Z;
	    int Num_Atoms;
    };

#endif
