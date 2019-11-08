#include <iostream>
#include <Ising.h>

using namespace std;

int main()
{
   Ising * Is = new Ising;

   Is->TotalEnergy(3);
   return 0; 
}