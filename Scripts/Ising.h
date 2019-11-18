#ifndef ISING_H
#define ISING_H

class Ising {
    private:
        int ** lattice;
        int N;
        double J;
    public:
        double avg_E;
        double avg_E2;
        double avg_M;
        double avg_M2;
        double avg_M_abs;
        double T;
        double E_tot;
        double C_v;
        double X;
        double sigma_E;
        double sigma_M;
        double Z;
        Ising();
        Ising(int N);
        ~Ising();
        void TotalEnergy(double);
        void Metropolis(int);
        void SpesificHeat();
        void Susceptibility();
        /*void MeanEnergy();
        void MeanMagnetization();
        void Susceptibility();*/
};

#endif //ISING_H
