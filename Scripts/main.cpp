#include <iostream>
#include <fstream>
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
    /*
    //Prints some of our end results
    cout << "total energy now: " << Is.E_tot << " J" << endl;
    cout << "avg_E: " << Is.avg_E << " J" << endl;
    cout << "avg_M: " << Is.avg_M << " J" << endl;
    cout << "avg_M_abs: " << Is.avg_M_abs << " J" << endl;
    cout << "Cv: " << Is.C_v << " enhet" << endl;
    cout << "X: " << Is.X << " enhet" << endl;
    */
//Torstein sitt
/*
    Is.Metropolis(10);
    cout << "total energy now: " << Is.E_tot << " J" << endl;
    cout << "avg_E: " << Is.avg_E << " J" << endl;
    cout << "avg_M: " << Is.avg_M << " J" << endl;
    cout << "Cv: " << Is.C_v << " enhet" << endl;
    cout << "X: " << Is.X << " enhet" << endl;
    */

    double dT = 0.01;
    int L = 40;

    ofstream myfile;
    myfile.open("4e.txt");

    Ising Isi = Ising(L);
    Isi.T = 2.0;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (2.3 - 2.0) / dT + 1; i++)
    {
        Isi.T = 2.0 + dT * i;
        Isi.Metropolis(10000);
        cout << "T: " << Isi.T << " K " << " Avg energy: " << Isi.avg_E << " J " << " Cv: " << Isi.C_v << " J " << " avg_M_abs: " << Isi.avg_M_abs << " J " << " X: " << Isi.X << " enhet" << endl;
        myfile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
    }
    myfile << endl;

    Isi.CreateLattice(L + 20);
    Isi.T = 2.0;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (2.3 - 2.0) / dT + 1; i++)
    {
        Isi.T = 2.0 + dT * i;
        Isi.Metropolis(10000);
        cout << "T: " << Isi.T << " K " << " Avg energy: " << Isi.avg_E << " J " << " Cv: " << Isi.C_v << " J " << " avg_M_abs: " << Isi.avg_M_abs << " J " << " X: " << Isi.X << " enhet" << endl;
        myfile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
    }
    myfile << endl;

    Isi.CreateLattice(L + 40);
    Isi.T = 2.0;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (2.3 - 2.0) / dT + 1; i++)
    {
        Isi.T = 2.0 + dT * i;
        Isi.Metropolis(10000);
        cout << "T: " << Isi.T << " K " << " Avg energy: " << Isi.avg_E << " J " << " Cv: " << Isi.C_v << " J " << " avg_M_abs: " << Isi.avg_M_abs << " J " << " X: " << Isi.X << " enhet" << endl;
        myfile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
    }
    myfile << endl;

    Isi.CreateLattice(L + 60);
    Isi.T = 2.0;
    Isi.TotalEnergy(1);
    for (int i = 0; i <= (2.3 - 2.0) / dT + 1; i++)
    {
        Isi.T = 2.0 + dT * i;
        Isi.Metropolis(10000);
        cout << "T: " << Isi.T << " K " << " Avg energy: " << Isi.avg_E << " J " << " Cv: " << Isi.C_v << " J " << " avg_M_abs: " << Isi.avg_M_abs << " J " << " X: " << Isi.X << " enhet" << endl;
        myfile << Isi.T << "  " << Isi.avg_E << "  " << Isi.C_v << "  " << Isi.avg_M_abs << "  " << Isi.X << endl;
    }
    myfile << endl;

    myfile.close();

    return 0;
}
