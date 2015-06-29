#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "Cube_Functions.h"

using namespace std;


void Cube_Generator(int Orbital_Number,bool isAlpha,char Checkpoint_File_Name[50])
{

	//Write cubegen command
	
	if(isAlpha==true)
	{	
	stringstream Cubegen_String;
	Cubegen_String << "cubegen 0 AMO=" <<Orbital_Number<<" "<<Checkpoint_File_Name<<" Alpha_Orbital_"<<Orbital_Number<<".cube"<<" -3 h";
		//Convert to c string for popen
		char* Cubegen_Input=new char[Cubegen_String.str().length()+1];  
		strcpy(Cubegen_Input,Cubegen_String.str().c_str());

		//Run cubegen
			FILE *fp = popen(Cubegen_Input,"r");
			pclose(fp);	
	}


	if(isAlpha==false)
	{
	stringstream Cubegen_String;
	Cubegen_String << "cubegen 0 BMO=" <<Orbital_Number<<" "<<Checkpoint_File_Name<<" Beta_Orbital_"<<Orbital_Number<<".cube"<<" -3 h";	
	

		//Convert to c string for popen
		char* Cubegen_Input=new char[Cubegen_String.str().length()+1];  
		strcpy(Cubegen_Input,Cubegen_String.str().c_str());

		//Run cubegen
			FILE *fp = popen(Cubegen_Input,"r");
			pclose(fp);
	}





return;
}
