#include "hopfield.hpp"

#include <iostream>
#include <stdexcept>
#include <fstream>


Hopfield::Hopfield(int N) : N(N), W(N*N, 0.0) {}

void Hopfield::train(const std::vector<std::vector<int>>& patterns) {
    int P{static_cast<int>(patterns.size())};

    for(int i{0}; i<N; ++i) {
        for(int j{0}; j<N; ++j) {
         
          if(j!=i) {
          double sum{0};
            for(int mu{0}; mu<P; ++mu)
            {
                sum+= (patterns[mu][i]*patterns[mu][j]);
            }
            w(i, j) = (sum/N);
          }
        }
    }
}

void Hopfield::printWeights() const {
    for(int i{0}; i<N; ++i) {
        for(int j{0}; j<N; ++j) {
            std::cout<<w(i,j)<<" ";
        }
     std::cout<<"\n";
    }
 std::cout<<"\n";
}

std::vector<int> Hopfield::recall(const std::vector<int>& input, int maxIter) {
    std::vector<int> state = input;

    for(int k{0}; k<maxIter; ++k) {
        bool convergence{true};
        for(int i{0}; i<N; ++i) {
            double h{0};

            for(int j{0}; j<N; ++j) {
                h+= (w(i,j)*state[j]);
            }
            int old= state[i];
            if(h>0) state[i]=1;
            else state[i]=-1;
            if(state[i]!=old) convergence=false;
        }
     if(convergence) break;
    }

    return state;
}

double Hopfield::energy(const std::vector<int>& state) const {
 double E{0};
    for(int i{0}; i<N; ++i) {
        for(int j{0}; j<N; ++j) {
        E+= w(i,j)*state[i]*state[j];
        }
    }
 return -0.5*E;
}

void Hopfield::saveWeights(const std::string& filename) const {

    std::ofstream file{filename};
    if(!file) {
        std::cerr<<"Il file non si è aperto, o non esiste\n";
        return;
    };

    for(int i{0}; i<N; ++i) {
        for(int j{0}; j<N; ++j) {
            file<<w(i,j)<<" ";
        }
     file<<"\n";
    }
}

void Hopfield::loadWeights(const std::string& filename) {

    std::ifstream file{filename};
    if(!file) {
        std::cerr<<"Il file non si è aperto, o non esiste\n";
        return;
    };

    for(int i{0}; i<N; ++i) {
        for(int j{0}; j<N; ++j) {
            file>>w(i,j);
        }
    }
}
