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
void Cube_Generator(string Cube_File_Name,string fchk_name, int orb_num)
{

    if (File_Exists(Cube_File_Name)){
    }
    
    else {
        string cubegen_command;

        cubegen_command="cubegen 0 MO=N fchk_name cube_name -3 h";
        cubegen_command.replace(cubegen_command.begin()+13,cubegen_command.begin()+14, to_string(orb_num));
        cubegen_command.replace(cubegen_command.end()-24,cubegen_command.end()-15, fchk_name);
        cubegen_command.replace(cubegen_command.end()-14,cubegen_command.end()-5, Cube_File_Name);
        
        cout << cubegen_command << '\n';
         
        printf ("Checking if processor is available...");
        if (system(NULL)) puts ("Ok");
            else exit (EXIT_FAILURE);
        cout << "Executing " << cubegen_command<<endl;
        system (cubegen_command.c_str());
    }
return;
}





