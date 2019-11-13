#include <iostream>
#include <random>
#include <utility>

#include <Ising.h>

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

void Ising::CreateLattice(const int N) {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, 1);
    
    this->N = N;
    this->lattice = new int*[N];
    for(int i = 0; i < N; i++){
        this->lattice[i] = new int[N];
        for(int j = 0; j < N; j++){
            this->lattice[i][j] = dis(gen)*2-1;
        }
    }
}

double Ising::TotalEnergy(double J)
{
    this->J = J;
    int N = this->N;
    double E_tot = 0;
    for(int i = 0; i < N; i += 2){
        for(int j = 0; j < N; j += 2){
            double E_step = 0;
            //sum with boundary conditions
            if(i == 0){
                E_step += lattice[N-1][j];
            }
            else{
                E_step += lattice[i-1][j];
            }
            if(j == 0){
                E_step += lattice[i][N-1];
            }
            else{
                E_step += lattice[i][j-1];
            }
            if(i == N-1){
                E_step += lattice[0][j];
            }
            else{
                E_step += lattice[i+1][j];
            }
            if(j == N-1){
                E_step += lattice[i][0];
            }
            else{
                E_step += lattice[i][j+1];
            }
            E_tot = J*(E_tot + E_step);
            }
         }

    for(int i = 1; i < N; i += 2){
        for(int j = 1; j < N; j += 2){
            double E_step = 0;
            E_step += lattice[i-1][j];
            E_step += lattice[i][j-1];
            if(i == N-1){
                E_step += lattice[0][j];
            }
            else{
                E_step += lattice[i+1][j];
            }
            if(j == N-1){
                E_step += lattice[i][0];
            }
            else{
                E_step += lattice[i][j+1];
            }
            E_tot = J*(E_tot + E_step);
        }
    }
    return E_tot;
}

struct deltaE{
    deltaE(double J){
        int deltaE[5] = {8*J, 4*J, 0, -4*J, -8*J};
    }
};

struct W{
    W(double J){
        int W[5] = {exp(8*J), exp(4*J), 1, exp(-4*J), exp(-8*J)};
    }
};

void Ising::Metropolis()
{
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, this->N-1);
    uniform_real_distribution<double> one_dis(0, 1);

    int J = this->J;
    int N2 = this->N*this->N;
    pair<int, int> index[N2];
    for(int i = 0; i < N2; i++) {
        int a = dis(gen);
        int b = dis(gen);
        index[i] = {a, b};
    }
    //W poop(this->J);
    double count = 0;
    double deltaEcalc;
    for(int i = 0; i < N2; i++) {
        if(index[i].first==0 and index[i].second==0) {
            //cout << "1" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[this->N-1][index[i].second]+lattice[index[i].first+1][index[i].second]+
            lattice[index[i].first][this->N-1]+lattice[index[i].first][index[i].second+1]);
        }
        else if(index[i].first==this->N-1 and index[i].second==0) {
            //cout << "2" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first-1][index[i].second]+lattice[0][index[i].second]+
            lattice[index[i].first][this->N]+lattice[index[i].first][index[i].second+1]);
        }
        else if(index[i].first==0 and index[i].second==this->N-1) {
            //cout << "2" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[this->N-1][index[i].second]+lattice[index[i].first+1][index[i].second]+
            lattice[index[i].first][index[i].second-1]+lattice[index[i].first][0]);
        }
        else if(index[i].first==0) {
            //cout << "1" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[this->N-1][index[i].second]+lattice[index[i].first+1][index[i].second]+
            lattice[index[i].first][index[i].second-1]+lattice[index[i].first][index[i].second+1]);
        }
        else if(index[i].second==0) {
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first-1][index[i].second]+lattice[index[i].first+1][index[i].second]+
            lattice[index[i].first][this->N-1]+lattice[index[i].first][index[i].second+1]);
        }
        else if(index[i].first==this->N-1 and index[i].second==this->N-1) {
            //cout << "2" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first-1][index[i].second]+lattice[0][index[i].second]+
            lattice[index[i].first][index[i].second-1]+lattice[index[i].first][0]);
        }
        else if(index[i].first==this->N-1) {
            //cout << "1" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first-1][index[i].second]+lattice[0][index[i].second]+
            lattice[index[i].first][index[i].second-1]+lattice[index[i].first][index[i].second+1]);
        }
        else if(index[i].second==this->N-1) {
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first-1][index[i].second]+lattice[index[i].first+1][index[i].second]+
            lattice[index[i].first][index[i].second-1]+lattice[index[i].first][0]);
        }
        else {
            //cout << "3" << endl;
            deltaEcalc = 2*J*lattice[index[i].first][index[i].second]*
            (lattice[index[i].first-1][index[i].second]+lattice[index[i].first+1][index[i].second]+
            lattice[index[i].first][index[i].second-1]+lattice[index[i].first][index[i].second+1]);
        }

        if(deltaEcalc <= 0) {
            lattice[index[i].first][index[i].second] *= -1;
        }
        else {
            double r = one_dis(gen);
            cout << r << endl;
        }
    }
}
