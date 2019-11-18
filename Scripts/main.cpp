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
    Is.Metropolis(10);
    cout << "total energy now: " << Is.E_tot << " J" << endl;
    cout << "avg_E: " << Is.avg_E << " J" << endl;
    cout << "avg_M: " << Is.avg_M << " J" << endl;
    Is.SpesificHeat();
    cout << "Cv: " << Is.C_v << " enhet" << endl;
    Is.Susceptibility();
    cout << "X: " << Is.X << " enhet" << endl;
    */
    int L = 40;
    Ising Isi = Ising(L);
    Isi.T = 2.0;
    Is.TotalEnergy(1);
    for (int i = 0; i <= 6; i++)
    {
        Isi.CreateLattice(L);
        Isi.T = 2.0 + 0.05 * i;
        Isi.Metropolis(10000);
        Isi.SpesificHeat();
        cout << "T: " << Isi.T << " K " << " Avg energy: " << Isi.avg_E << " J " << " Cv: " << Isi.C_v << " J " << " avg_M: " << Is.avg_M << " J " << " X: " << Is.X << " enhet" << endl;
    }

    return 0;
}
