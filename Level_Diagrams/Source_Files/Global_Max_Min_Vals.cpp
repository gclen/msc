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
#include <algorithm>

#include "Level_Diagram_Functions.h"

using namespace std;

struct Global_Vals Global_Max_Min_Vals(vector <struct Bin_Struct> &projection_bins, struct Global_Vals &Bins_Max_Min)
{
    vector<double> wfn_sums;
    double min_sum,max_sum;
    
    //Loop over the structs and put the sums into another vector
    for (int i=0;i<projection_bins.size();i++){
        wfn_sums.push_back(projection_bins[i].wfn_sq_sum);
    }
    
    //Find the min and max sums
    auto min_max_sums = minmax_element(wfn_sums.begin(),wfn_sums.end());
    min_sum = wfn_sums[min_max_sums.first-wfn_sums.begin()];
    max_sum = wfn_sums[min_max_sums.second-wfn_sums.begin()];    

    //If the max and min are the initialized values of -1 
    //then set the max and min to the first bin values
    if (Bins_Max_Min.glob_min_sum == -1.0){
        Bins_Max_Min.glob_min_sum=min_sum;                   
    }

    if (Bins_Max_Min.glob_max_sum == -1.0){
        Bins_Max_Min.glob_max_sum=max_sum;                   
    }
       
    //If the current max or min should be the new global values then set them 
    if (min_sum < Bins_Max_Min.glob_min_sum){
        Bins_Max_Min.glob_min_sum=min_sum;
    }
    if (max_sum > Bins_Max_Min.glob_max_sum){
        Bins_Max_Min.glob_max_sum=max_sum;
    }    
            

return Bins_Max_Min;
}