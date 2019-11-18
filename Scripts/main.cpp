#include <iostream>
#include <Ising.h>

using namespace std;

int main()
{
   Ising Is = Ising(2);
   Is.T = 1.0;
   Is.TotalEnergy(1);
   cout << "total energy: " << Is.E_tot << " J" << endl;

   Is.Metropolis(100000);
   cout << "total energy now: " << Is.E_tot << " J" << endl;
   cout << "avg_E: " << Is.avg_E << " J" << endl;
   cout << "avg_M: " << Is.avg_M << " J" << endl;
   cout << "avg_M_abs: " << Is.avg_M_abs << " J" << endl;
   cout << "Cv: " << Is.C_v << " enhet" << endl;
   cout << "X: " << Is.X << " enhet" << endl;
   return 0; 
}
