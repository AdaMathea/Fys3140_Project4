#ifndef ISING_H
#define ISING_H

class Ising {
    private:
        void CreateLattice(const int);
        int ** lattice;
        int N;
        double J;
    public:
        double avg_E;
        double avg_E2;
        double avg_M;
        double avg_M2;
        double T;
        double E_tot;
        double C_v;
        double X;
        double sigma_E;
        double sigma_M;
        Ising();
        Ising(int N);
        ~Ising();
        double TotalEnergy(double);
        void Metropolis(int);
        void SpesificHeat();
        void Susceptibility();
};

#endif //ISING_H