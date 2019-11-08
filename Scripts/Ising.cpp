#include <iostream>
#include <random>

#include <Ising.h>

using namespace std;

double Ising::TotalEnergy(int N, double J)
{
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0, 1);
    
    int lattice[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            lattice[i][j] = dis(gen)*2-1;
        }
    }
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
