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
    net.printWeights();
    net.saveWeights("weights.txt");

    Hopfield net2(N);
    net2.loadWeights("weights.txt");
    net2.printWeights();

    std::vector<int> corrupted = {1, -1, 1, -1};
    std::vector<int> recovered = net.recall(corrupted);

    std::cout << "Energia corrotto: " << net.energy(corrupted) << "\n";
    std::cout << "Energia recovered: " << net.energy(recovered) << "\n";

    std::vector<int> recovered2 = net2.recall(corrupted);


    std::cout << "Pattern corrotto: ";
    for(int v : corrupted) std::cout << v << " ";
    std::cout <<"\n";

    std::cout << "Pattern recuperato: ";
    for(int v : recovered) std::cout << v << " ";
    std::cout <<"\n";

    std::cout << "Atteso: -1 1 1 -1\n";


    std::vector<int> p = loadPattern("pic1_rgb.png", 100);
    std::cout << "Pixel caricati: " << p.size() << "\n";

    return 0;
}
