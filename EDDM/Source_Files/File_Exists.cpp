#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "Cube_Functions.h"

using namespace std;

bool File_Exists(char Test_File[50]){

    ifstream input_file(Test_File);
    if (input_file.good()){
        input_file.close();
        return true;
    }
    else{
        input_file.close();
        return false;
    }
}




