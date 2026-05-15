#ifndef HOPFIELD_HPP
#define HOPFIELD_HPP

#include <vector>
#include <string> 

class Hopfield {

public:

    explicit Hopfield(int N);

    void train(const std::vector<std::vector<int>>& patterns);

    std::vector<int> recall(const std::vector<int>& input, int maxIter = 100);

    double energy(const std::vector<int>& state) const;

    void saveWeights(const std::string& filename) const;

    void loadWeights(const std::string& filename);

    void printWeights() const;

private:

    int N;
    std::vector<double> W;

    double& w(int i, int j) { return W[i*N + j]; }
    double w(int i, int j) const { return W[i*N + j]; }

};

#endif