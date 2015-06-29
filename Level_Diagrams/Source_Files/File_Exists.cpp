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

bool File_Exists(string Test_File){

    ifstream input_file(Test_File.c_str());
    if (input_file.good()){
        input_file.close();
        return true;
    }
    else{
        input_file.close();
        return false;
    }
}







