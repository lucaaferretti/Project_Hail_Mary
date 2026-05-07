#include "hopfield.hpp"

#include <stdexcept>


Hopfield::Hopfield(int N) : N(N), W(N*N, 0.0) {}

void Hopfield::train(const std::vector<std::vector<int>>& patterns) {


    (void)patterns;
}

std::vector<int> Hopfield::recall(const std::vector<int>& input, int maxIter) {

    (void)maxIter;
    return input;
}

double Hopfield::energy(const std::vector<int>& state) const {


    return 0.0;
}

void Hofield::saveWeights(const std::string& filename) const {

    (void)filename;
}

void Hofield::loadWeights(const std::string& filename) const {

    (void)filename;
}