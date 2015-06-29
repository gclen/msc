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
void Write_Scaled_Sums(vector <struct Bin_Struct> &bin_data, double Energy)
{
    ofstream Data_write; 
    Data_write.open("projected_sums.txt",ios::app);

    for (int i=0;i<bin_data.size();i++){
        Data_write << Energy << " " << bin_data[i].dist_to_bin << " " << bin_data[i].scaled_sum <<endl;
    }
    
    Data_write << "--- --- ---" << endl;

return;
}

