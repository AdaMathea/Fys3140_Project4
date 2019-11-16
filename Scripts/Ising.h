#ifndef ISING_H
#define ISING_H
#include <utility>

class Ising {
    private:
        void CreateLattice(const int);
        int ** lattice;
        int N;
        double J;
    public:
        double avg_E;
        double avg_E2;
        double T;
        double E_tot;
        double C_v;
        double sigma_E;
        Ising();
        Ising(int N);
        ~Ising();
        double TotalEnergy(double);
        void Metropolis(int);
        void SpesificHeat();
        /*void MeanEnergy();
        void MeanMagnetization();
        void SpesificHeat();
        void Susceptibility();*/
};

#endif //ISING_H