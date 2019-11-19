#include <iostream>
#include <Ising.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

int main()
{
    //Runs class for 2x2 lattice, T = 1 and J = 1
    Ising Is = Ising(2);
    Is.T = 1.0;
    Is.TotalEnergy(1);

    //Prints total energy in the start
    cout << "total energy: " << Is.E_tot << " J" << endl;

    int val = 100000;
    //Write to file
    ostringstream oss;
    oss << "MC_tot_" << val << ".txt";
    string filename = oss.str();
    ofstream myfile(filename, ofstream::out);
    for (int n = 1; n <= 100; n++) {
        //Runs Monte Carlo with 100 000 cycles
        Is.Metropolis(val);
        myfile << Is.avg_E << " " << Is.avg_M << " " << 
        Is.avg_M_abs << " " << Is.C_v << " " << Is.X << endl;
    }
    myfile.close();

    //Prints some of our end results
    cout << "total energy now: " << Is.E_tot << " J" << endl;
    cout << "avg_E: " << Is.avg_E << " J" << endl;
    cout << "avg_M: " << Is.avg_M << " J" << endl;
    cout << "avg_M_abs: " << Is.avg_M_abs << " J" << endl;
    cout << "Cv: " << Is.C_v << " enhet" << endl;
    cout << "X: " << Is.X << " enhet" << endl;


    // Runs class for 40 x 40 lattice, T = [2.0, 2.3] and J = 1
    double dT = 0.01;   // Defines stepsize for the temperature
    int L = 40;
    double T_start = 2.0;   // start of temperature interval
    double T_slutt = 2.3;   // end of temperature interval

    ofstream myefile;
    myefile.open("4e.txt");
    myefile << "  T     <E>     Cv        <|M|>       X" << endl;

    Ising Isi = Ising(L);   // load Ising class
    Isi.T = T_start;        // initialises
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (T_slutt - T_start) / dT + 1; i++) // loops over T, calculates values and prints values to file
    {
        Isi.Metropolis(10000);
        myefile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
        Isi.T += dT;
    }
    myefile << endl;

    // Runs class for 60 x 60 lattice, T = [2.0, 2.3] and J = 1
    Isi.CreateLattice(L + 20);
    Isi.T = T_start;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (T_slutt - T_start) / dT + 1; i++)
    {
        Isi.Metropolis(10000);
        myefile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
        Isi.T += dT;
    }
    myefile << endl;

    // Runs class for 80 x 80 lattice, T = [2.0, 2.3] and J = 1
    Isi.CreateLattice(L + 40);
    Isi.T = T_start;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (T_slutt - T_start) / dT + 1; i++)
    {
        Isi.Metropolis(10000);
        myefile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
        Isi.T += dT;
    }
    myefile << endl;

    // Runs class for 100 x 100 lattice, T = [2.0, 2.3] and J = 1
    Isi.CreateLattice(L + 60);
    Isi.T = T_start;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (T_slutt - T_start) / dT + 1; i++)
    {
        Isi.Metropolis(10000);
        myefile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
        Isi.T += dT;
    }
    myefile << endl;

    myefile.close();

    return 0;
}
