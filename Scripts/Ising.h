#ifndef ISING_H
#define ISING_H

class Ising {
    private:
        int ** lattice;
        double J;
    public:
        //Values
        int N;
        double avg_E;
        double avg_E2;
        double avg_M;
        double avg_M2;
        double avg_M_abs;
        double T;
        double E_tot;
        double M_tot;
        double C_v;
        double X;
        double sigma_E;
        double sigma_M;
        double Z;

        //Functions
        Ising();
        Ising(int N);
        ~Ising();
        void TotalEnergy(double);
        void Metropolis(int);
        void CreateLattice(int);
};

#endif //ISING_H
