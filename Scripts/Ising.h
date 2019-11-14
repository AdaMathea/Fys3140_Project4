#ifndef ISING_H
#define ISING_H

class Ising {
    private:
        void CreateLattice(const int);
        int ** lattice;
        int N;
        double J;
    public:
        double avg;
        double T;
        double E_tot;
        Ising();
        Ising(int N);
        ~Ising();
        double TotalEnergy(double);
        void Metropolis(int);
        /*void MeanEnergy();
        void MeanMagnetization();
        void SpesificHeat();
        void Susceptibility();*/
};

#endif //ISING_H