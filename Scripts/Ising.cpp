#include <iostream>
#include <random>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>

#include <Ising.h>
using namespace std;

//Constructor
Ising::Ising(){
    this->CreateLattice(5);
}

//Constructor with input
Ising::Ising(int N) {
    this->CreateLattice(N);
}

//Deconstructor
Ising::~Ising() {
    for(int i = 0; i < this->N; i++) {
        delete this->lattice[i];
    }
    delete this->lattice;
}

//Boundary conditions
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
            this->lattice[i][j] = dis(gen)*2-1;
            //this->lattice[i][j] = 1; If you want to make a specific lattice
        }
    }
}

//Initialice total energy
void Ising::TotalEnergy(double J) {
    this->J = J;
    int N = this->N;
    int E_step = 0;
    int M_step = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (this->T < 1.5) lattice[i][j] = 1;
            M_step += lattice[i][j];
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            E_step += lattice[i][j]*lattice[i][periodic(j,N,-1)];
            E_step += lattice[i][j]*lattice[periodic(i,N,-1)][j];
        }
    }
    this->M_tot = M_step;
    this->E_tot = E_step*(-J);
}

void Ising::Metropolis(int cycles) {
    this->avg_E = 0;
    this->avg_E2 = 0;
    this->avg_M = 0;
    this->avg_M2 = 0;
    this->avg_M_abs = 0;
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, this->N-1);
    uniform_real_distribution<double> one_dis(0.0, 1.0);
    
    //Sets initial values
    int N = this->N;
    double E = this->E_tot;
    double M = this->M_tot;
    int J = this->J;
    int T = this->T;
    int N2 = N*N;
    
    //Chooses random points to use in our Monte Carlo method
    pair<int, int> index[N2];
    for(int i = 0; i < N2; i++) {
        int a = dis(gen);
        int b = dis(gen);
        index[i] = {a, b};
    }
    /*
    //Write to file
    ostringstream oss;
    oss << "MC_" << cycles << ".txt";
    string filename = oss.str();
    ofstream myfile(filename, ofstream::out);
    */

    for(int l = 0; l < cycles; l++) {
        //Monte Carlo cycles
        for(int i = 0; i < N2; i++) {
            //Calculates the difference between the previous and new energy
            double deltaEcalc = 2*J*
            lattice[index[i].first][index[i].second]*(
                lattice[index[i].first][periodic(index[i].second,N,-1)]+
                lattice[periodic(index[i].first,N,-1)][index[i].second] +
                lattice[index[i].first][periodic(index[i].second,N,1)] +
                lattice[periodic(index[i].first,N,1)][index[i].second]
            );

            if(deltaEcalc <= 0) {
                lattice[index[i].first][index[i].second] *= -1;
                E += (double) deltaEcalc;
                M += (double) 2*lattice[index[i].first][index[i].second];
            }
            else {
                double prob = exp(-deltaEcalc/T); //probability for a flip
                double r = one_dis(gen);
                if(r <= prob){
                    //Runs based on a probability
                    lattice[index[i].first][index[i].second] *= -1;
                    E += (double) deltaEcalc;
                    M += (double) 2*lattice[index[i].first][index[i].second];
                }
            }
        }
        //Summing up values
        this->avg_E += E;
        this->avg_E2 += E*E;
        this->avg_M += M;
        this->avg_M2 += M*M;
        this->avg_M_abs += abs(M);
        /*
        myfile << this->avg_E/double(l*N2) << " " << this->avg_M/double(l*N2) << " " << 
        this->avg_M_abs/double(l*N2) << " " << E << " " <<
        (this->avg_E2-(this->avg_E*this->avg_E))/(double(N2)*this->T*this->T*l) << " " << 
        (this->avg_M2-(this->avg_M*this->avg_M))/(double(N2)*this->T*l) << " " << l << endl;
        */
    }
    //myfile.close();
    //Total energy in the end:
    this->E_tot = E; 

    // Normalizes by cycless
    avg_E /= double(cycles);
    avg_E2 /= double(cycles);
    avg_M /= double(cycles);
    avg_M2 /= double(cycles);
    avg_M_abs /= double(cycles);

    // calculates quantities
    this->sigma_E = (avg_E2-(avg_E*avg_E))/(double(N2));
    this->C_v = sigma_E/(this->T*this->T);
    this->avg_E = avg_E/((double) N2);
    this->avg_E2 = avg_E2/((double) N2);
    this->sigma_M = (avg_M2-(avg_M*avg_M))/(double(N2));
    this->X = sigma_M/this->T;
    this->avg_M = avg_M/((double) N2);
    this->avg_M2 = avg_M2/((double) N2);
    this->avg_M_abs = avg_M_abs/((double) N2);
};