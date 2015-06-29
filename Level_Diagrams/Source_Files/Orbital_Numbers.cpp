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
struct Orbital_Struct Get_Orbital_Numbers(Orbital_Struct &Orb_Info, int Num_Occ, int Num_Virt)
{
    vector<int> orb_nums;
    int HOMO_num;
    
    //HOMO corresponds to the number of occupied eigenvalues
    HOMO_num=Orb_Info.Occupied_Eng.size();

    //Get the occupied orbital numbers
    for (int i=(HOMO_num-Num_Occ+1);i<=HOMO_num;i++){
        orb_nums.push_back(i);
    }   
    //Get the virtual orbital numbers
    for (int j=(HOMO_num+1);j<=(HOMO_num+Num_Virt);j++){
        orb_nums.push_back(j);
    }

    Orb_Info.Orb_Nums_Vec=orb_nums;

return Orb_Info;
}

