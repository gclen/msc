#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main()
{
char Velocity_Output_File[20],Init_Velocity_Num[20];
long double Velocity[132],Random_Velocity;
int Output_Count=1,Rand_Int=0;
double Velocity_Sign=1.0;

//Initialize output stream
ofstream Velocity_Output;
Velocity_Output.open("Init_Velocity_200K");
 
srand((unsigned)time(0));

for(int i=0; i<132; i++)
{
Random_Velocity=0.000004+((0.0009)*rand())/(RAND_MAX+1.0);
Rand_Int=rand()%100+1;
if (Rand_Int%2==1)
{
Velocity_Sign=-1.0;
}
if(Rand_Int%2==0)
{
Velocity_Sign=1.0;
}

Velocity[i]=Random_Velocity*Velocity_Sign;
}

for (int n=0;n<132;n++)
{
Velocity_Output << Velocity[n] << " ";
if(Output_Count%3==0)
{
Velocity_Output << endl;
}
Output_Count=Output_Count+1;
}

return 0;
}
