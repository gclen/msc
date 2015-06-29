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
struct Orbital_Struct Energy_Read(string G09_output_file)
{
    struct Orbital_Struct Orb_Info;
    int BUFF_SIZE=32768;
    char buffer[BUFF_SIZE];
    vector<double> Occ_Energies_Ha;
    vector<double> Virt_Energies_Ha;
    vector<double> Occ_Energies_eV;
    vector<double> Virt_Energies_eV;
    string head_1,head_2,head_3,head_4,eng_1,eng_2,eng_3,eng_4,eng_5; 

    //Input file 
    ifstream log_input;
    log_input.open(G09_output_file.c_str());

        while(log_input.good()== false)
        {
            cout << "Unable to open Gaussian09 log file. Enter a new name: ";
            cin >> G09_output_file;
            // Clear the file stream
            log_input.clear();
            log_input.open(G09_output_file.c_str());
        }
    //Read file line by line    
    while (log_input.getline(buffer,BUFF_SIZE)){
        
            //If it is at the end of the log file then exit the loop 
            if (strstr(buffer,"Normal termination of Gaussian") != NULL){
                break;
            }
            else if (strstr(buffer,"Population analysis using the SCF density.")){
                Occ_Energies_Ha.clear();
                Virt_Energies_Ha.clear();
            }
            else if (strstr(buffer, "Alpha  occ.") && strstr(buffer, ". eigenvalues --")){
                
                istringstream ss(buffer);
                //Skip past the header
                ss >> head_1 >> head_2 >> head_3 >> head_4;
                //Put energies into vector
                ss >> eng_1;
                Occ_Energies_Ha.push_back(atof(eng_1.c_str()));
                if (ss >> eng_2){
                    Occ_Energies_Ha.push_back(atof(eng_2.c_str()));
                    if (ss >> eng_3){
                        Occ_Energies_Ha.push_back(atof(eng_3.c_str()));
                        if (ss >> eng_3){
                            Occ_Energies_Ha.push_back(atof(eng_3.c_str()));
                            if (ss >> eng_4){
                                Occ_Energies_Ha.push_back(atof(eng_4.c_str()));
                                if (ss >> eng_5){
                                    Occ_Energies_Ha.push_back(atof(eng_5.c_str()));
                                }
                            }
                        }
                    }
                }
            }
            else if (strstr(buffer, "Alpha virt.") && strstr(buffer, ". eigenvalues --")){
                
                istringstream ss(buffer);
                //Skip past the header
                ss >> head_1 >> head_2 >> head_3 >> head_4;

                //Put energies into vector
                ss >> eng_1;
                Virt_Energies_Ha.push_back(atof(eng_1.c_str()));
                if (ss >> eng_2){
                    Virt_Energies_Ha.push_back(atof(eng_2.c_str()));
                    if (ss >> eng_3){
                        Virt_Energies_Ha.push_back(atof(eng_3.c_str()));
                        if (ss >> eng_3){
                            Virt_Energies_Ha.push_back(atof(eng_3.c_str()));
                            if (ss >> eng_4){
                                Virt_Energies_Ha.push_back(atof(eng_4.c_str()));
                                if (ss >> eng_5){
                                    Virt_Energies_Ha.push_back(atof(eng_5.c_str()));
                                }
                            }
                        }
                    }
                }            
            }
        
    }
    log_input.close();

    //Convert energies into eV
    //Occupied
    for (int i=0;i<Occ_Energies_Ha.size();i++){
        Occ_Energies_eV.push_back(Occ_Energies_Ha[i]*27.21138505);
    }
    //Virtual
    for (int j=0;j<Virt_Energies_Ha.size();j++){
        Virt_Energies_eV.push_back(Virt_Energies_Ha[j]*27.21138505);
    }

    Orb_Info.Occupied_Eng=Occ_Energies_eV;
    Orb_Info.Virtual_Eng=Virt_Energies_eV;

return Orb_Info;
}



