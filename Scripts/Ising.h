#ifndef ISING_H
#define ISING_H

class Ising {
    private:
        void CreateLattice(const int);
        int ** lattice;
        int N;
        double J;
    public:
        Ising();
        Ising(int N);
        ~Ising();
        double TotalEnergy(double);
        void Metropolis();
        /*void MeanEnergy();
        void MeanMagnetization();
        void SpesificHeat();
        void Susceptibility();*/
};

#endif //ISING_H