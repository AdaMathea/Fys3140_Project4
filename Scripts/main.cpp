#include <iostream>
#include <Ising.h>

using namespace std;

int main()
{
   Ising * Is = new Ising;

   double val = Is->TotalEnergy(1);
   cout << "total energy: " << val << " J" << endl;
   return 0; 
}