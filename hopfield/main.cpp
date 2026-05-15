#include <iostream>
#include <vector>
#include "pattern.hpp"
#include "hopfield.hpp"
//Questa è solo una bozza da cui partire
int main() {
/*
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

*/
std::cout << "=== TEST CON IMMAGINE REALE ===\n\n";
 
const int SIZE{100};
const std::string OUT = "rebuiltedImages/";

// Lista dei file da caricare
std::vector<std::string> filenames = {
    "images/pic1_rgb.png",
    "images/mao_zedong.png",
    "images/SixSeven.png",
    "images/TungTungSahur.png"
};

// Carica tutti i pattern in un ciclo
std::vector<std::vector<int>> patterns;
for (const std::string& f : filenames) {
    patterns.push_back(loadPattern(f, SIZE));
    std::cout << "Caricata: " << f << "\n";
}

// Addestra la rete su tutti i pattern
Hopfield net(SIZE * SIZE);
net.train(patterns);
std::cout << "Training completato su " << patterns.size() << " immagini\n\n";

// Salva originali, corrompi e fai recall in un ciclo
for (int i = 0; i < static_cast<int>(patterns.size()); ++i) {
    std::string idx = std::to_string(i + 1);

    // Salva originale
    savePattern(patterns[i], SIZE, SIZE, OUT + "originale" + idx + ".png");

    // Corrompi e salva
    std::vector<int> corrupted = corruptPattern(patterns[i], 0.3);
    savePattern(corrupted, SIZE, SIZE, OUT + "corrotta" + idx + ".png");

    // Taglia e salva
    std::vector<int> cut = cutPattern(patterns[i], SIZE, SIZE);
    savePattern(cut, SIZE, SIZE, OUT + "tagliata" + idx + ".png");

    // Recall e salva
    std::vector<int> recovered = net.recall(corrupted);
    savePattern(recovered, SIZE, SIZE, OUT + "recuperata" + idx + ".png");

    // Energie
    std::cout << "=== Immagine " << idx << " ===\n";
    std::cout << "Energia originale:  " << net.energy(patterns[i]) << "\n";
    std::cout << "Energia corrotta:   " << net.energy(corrupted)   << "\n";
    std::cout << "Energia recuperata: " << net.energy(recovered)   << "\n\n";
}
 
    return 0;
}
