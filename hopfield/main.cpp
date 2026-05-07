#include <iostream>
#include <vector>
#include "pattern.hpp"
#include "hopfield.hpp"
//Questa è solo una bozza da cui partire
int main() {

    const int N{4};

    std::vector<std::vector<int>> patterns = {
        {-1, 1, 1, -1},
        {1, -1, -1, 1}
    };

    Hopfield net(N);
    net.train(patterns);
    std::cout << "Training completato\n";

    std::vector<int> corrupted = {1, -1, 1, -1};
    std::vector<int> recovered = net.recall(corrupted);

    std::cout << "Pattern corrotto: ";
    for(int v : corrupted) std::cout << v << " ";
    std::cout <<"\n";

    std::cout << "Pattern recuperato: ";
    for(int v : recovered) std::cout << v << " ";
    std::cout <<"\n";

    std::cout << "Atteso: -1 1 1 -1\n";

    return 0;
}