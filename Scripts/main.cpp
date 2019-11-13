#include <iostream>
#include <Ising.h>

using namespace std;

int main()
{
   Ising Is = Ising();

   double val = Is.TotalEnergy(1);
   cout << "total energy: " << val << " J" << endl;

   Is.Metropolis();
   return 0; 
}