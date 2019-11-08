#include <iostream>
#include <random>

#include <Ising.h>

using namespace std;

int Ising::TotalEnergy(int N)
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
    for(i = 0; i < N+1; i += 2){
        for(j = 0; j < N+1; i += 2){
            
        }
    }
}   
