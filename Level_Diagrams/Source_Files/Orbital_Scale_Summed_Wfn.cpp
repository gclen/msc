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

vector<struct Bin_Struct> Orbital_Scale_Summed_Wfn(vector <struct Bin_Struct> &projection_bins)
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

    for (int i=0; i< projection_bins.size();i++){
        projection_bins[i].scaled_sum=1.0-(projection_bins[i].wfn_sq_sum-min_sum)/(max_sum-min_sum);
    }
    

return projection_bins;
}
