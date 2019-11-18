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
   Is.SpesificHeat();
   cout << "Cv: " << Is.C_v << " enhet" << endl;
   Is.Susceptibility();
   cout << "X: " << Is.X << " enhet" << endl;
   return 0; 
    Is.Metropolis(10);
    cout << "total energy now: " << Is.E_tot << " J" << endl;
    cout << "avg energy: " << Is.avg_E << " J" << endl;
    Is.SpesificHeat();
    cout << "Cv: " << Is.C_v << " J" << endl;

    Ising Isi = Ising(40);
    Isi.T = 2.0;
    for (int j = 0; j <= 6; j++)
    {
        0.05 * j;
    }
    for (int i = 0; i <= 6; i++)
    {
        Isi.T = 2.0 + 0.05 * i;
        Isi.Metropolis(10);
        Isi.SpesificHeat();
        cout << "T: " << Isi.T << " K " << " Avg energy: " << Isi.avg_E << " J " << " Cv: " << Isi.C_v << " J" << endl;
    }
    return 0;
}
