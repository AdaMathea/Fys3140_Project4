#include <iostream>
#include <random>
#include <utility>

#include <Ising.h>
double EPS = 0.0001;
using namespace std;

Ising::Ising(){
    this->CreateLattice(5);
}

Ising::Ising(int N) {
    this->CreateLattice(N);
}

Ising::~Ising() {
    for(int i = 0; i < this->N; i++) {
        delete this->lattice[i];
    }
    delete this->lattice;
}

inline int periodic(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}

void Ising::CreateLattice(const int N) {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, 1);
    
    this->N = N;
    this->J = 1;
    this->lattice = new int*[N];
    for(int i = 0; i < N; i++){
        this->lattice[i] = new int[N];
        for(int j = 0; j < N; j++){
            //this->lattice[i][j] = dis(gen)*2-1;
            this->lattice[i][j] = 1;
        }
    }
    //cout << this->lattice[0][0] << this->lattice[1][0] << endl;
    //cout << this->lattice[0][1] << this->lattice[1][1] << endl;
}

//Initialice total energy
double Ising::TotalEnergy(double J) {
    this->J = J;
    int N = this->N;
    int E_step = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            E_step += lattice[i][j]*lattice[i][periodic(j,N,-1)];
            E_step += lattice[i][j]*lattice[periodic(i,N,-1)][j];
        }
    }
    this->E_tot = E_step*(-J);
}

void Ising::Metropolis(int cycles) {

    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, this->N-1);
    uniform_real_distribution<double> one_dis(0, 1);

    double E = this->E_tot;
    double M = 0;
    int J = this->J;
    int T = this->T;
    int N2 = this->N*this->N;
    pair<int, int> index[N2];
    for(int i = 0; i < N2; i++) {
        int a = dis(gen);
        int b = dis(gen);
        index[i] = {a, b};
    }
    double deltaEcalc;
    for(int l = 0; l < cycles; l++) {
        for(int i = 0; i < N2; i++) {
            int deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first][periodic(index[i].second,N,-1)]+
            lattice[periodic(index[i].first,N,-1)][index[i].second] +
            lattice[index[i].first][periodic(index[i].second,N,1)] +
            lattice[periodic(index[i].first,N,1)][index[i].second]);

            if(deltaEcalc <= 0) {
                lattice[index[i].first][index[i].second] *= -1;
                E += deltaEcalc;
                M += 2*lattice[index[i].first][index[i].second];
            }
            else {
                double prob = exp(-deltaEcalc/T); //probability for a flip
                double r = one_dis(gen);
                if(r <= prob){
                    //cout << r << endl;
                    lattice[index[i].first][index[i].second] *= -1;
                    E += deltaEcalc;
                    M += 2*lattice[index[i].first][index[i].second];
                }
            }
            this->avg_E += E;
            this->avg_E2 += E*E;
            this->avg_M += M;
            this->avg_M2 += M*M;
        }
    }
    this->E_tot = E; 
    this->avg_E = avg_E/((double) cycles*N2*N2);
    this->avg_E2 = avg_E2/((double) cycles*N2*N2);
    this->avg_M = avg_M/((double) cycles*N2*N2);
    this->avg_M2 = avg_M2/((double) cycles*N2*N2);
};

void Ising::SpesificHeat() {
    this->sigma_E = avg_E2-(avg_E*avg_E);
    this->C_v = sigma_E/this->T;
}

void Ising::Susceptibility() {
    this->sigma_M = avg_M2-(avg_M*avg_M);
    this->X = sigma_M/this->T;
}
