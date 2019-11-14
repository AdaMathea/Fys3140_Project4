#include <iostream>
#include <random>
#include <utility>

#include <Ising.h>

#define k_b 1.38*pow(10, -23)
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
            this->E_tot = J*(E_tot + E_step);
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
            this->E_tot = J*(E_tot + E_step);
        }
    }
    return this->E_tot;
}

struct deltaE{
    double data[5];
    deltaE(double J) {
        data[0] = 8*J;
        data[1] = 4*J;
        data[2] = 0;
        data[3] = -4*J;
        data[4] = -8*J;
    }
};

struct W{
    double w[5];
    W(double J, double T){
        w[0] = exp((1/T*k_b)*8*J);
        w[1] = exp((1/T*k_b)*4*J);
        w[2] = 1;
        w[3] = exp((1/T*k_b)*-4*J);
        w[4] = exp((1/T*k_b)*-8*J);
    }
};

void Ising::Metropolis(int cycles) {

    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, this->N-1);
    uniform_real_distribution<double> one_dis(0, 1);

    double E = this->E_tot;
    int J = this->J;
    int T = this->T;
    int N2 = this->N*this->N;
    pair<int, int> index[N2];
    for(int i = 0; i < N2; i++) {
        int a = dis(gen);
        int b = dis(gen);
        index[i] = {a, b};
    }
    W W(J, T);
    deltaE deltaE(J);
    cout << E << endl;
    double deltaEcalc;
    for(int l = 0; l < cycles; l++) {
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
                //cout << "1" << endl;
                lattice[index[i].first][index[i].second] *= -1;
                E += deltaEcalc;
                /*
                for(int k = 0; k < 5; k++) {
                    
                    if(abs(deltaEcalc - (deltaE.data[k])) <= EPS) {
                        this->E_tot = this->E_tot - deltaE.data[k];
                    }
                }
                */
            }
            else {
                //cout << "2" << endl;
                double r = one_dis(gen);
                for(int j = 0; j < 5; j++) {
                    if(abs(deltaEcalc - (deltaE.data[j])) <= EPS) {
                        if(r <= W.w[j]) {
                            lattice[index[i].first][index[i].second] *= -1;
                            //this->E_tot = this->E_tot - deltaE.data[j];
                            E += deltaEcalc;
                        }
                    }
                }
            }
            
            cout << E << endl;
        }
    }
    //cout << E << endl;
    this->avg = E/cycles;
};
