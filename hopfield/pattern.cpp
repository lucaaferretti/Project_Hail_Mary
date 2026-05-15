#include "pattern.hpp"

#include <SFML/Graphics.hpp>
#include <stdexcept>

// loadPattern
// 1. Carica l'immagine con sf::Image
// 2. La ridimensiona in una sf::Image di dimensioni targetN x targetN
//    usando un RenderTexture + Sprite scalato
// 3. Per ogni pixel calcola la luminosità media (R+G+B)/3:
//    >= 128  ->  +1  (chiaro / bianco)
//     < 128  ->  -1  (scuro  / nero)
std::vector<int> loadPattern(const std::string& filename, int targetN) {
 
// Caricamento immagine originale dal file 
    sf::Image srcImage;
    if (!srcImage.loadFromFile(filename)) {
        throw std::runtime_error("loadPattern: impossibile aprire il file \"" + filename + "\"");
    }
 
    // Ridimensionamento tramite RenderTexture
    sf::Texture srcTexture;
    srcTexture.loadFromImage(srcImage);
 
    sf::RenderTexture rt;
    if (!rt.create(static_cast<unsigned int>(targetN),
                   static_cast<unsigned int>(targetN))) {
        throw std::runtime_error("loadPattern: impossibile creare RenderTexture");
    }
 
    sf::Sprite sprite(srcTexture);
    // Calcola fattori di scala per adattare l'immagine a targetN x targetN
    float scaleX = static_cast<float>(targetN) / static_cast<float>(srcImage.getSize().x);
    float scaleY = static_cast<float>(targetN) / static_cast<float>(srcImage.getSize().y);
    sprite.setScale(scaleX, scaleY);
 
    rt.clear(sf::Color::White);
    rt.draw(sprite);
    rt.display();
 
    // Leggi i pixel dalla RenderTexture
    sf::Image scaled = rt.getTexture().copyToImage();
 
    // Conversione pixel -> {+1, -1} 
    std::vector<int> pattern;
    pattern.reserve(static_cast<size_t>(targetN * targetN));
 
    for (unsigned int y = 0; y < static_cast<unsigned int>(targetN); ++y) {
        for (unsigned int x = 0; x < static_cast<unsigned int>(targetN); ++x) {
            sf::Color c = scaled.getPixel(x, y);
            // Luminosità media semplice
            int brightness = (static_cast<int>(c.r) +
                              static_cast<int>(c.g) +
                              static_cast<int>(c.b)) / 3;
            pattern.push_back(brightness >= 128 ? +1 : -1);
        }
    }
 
    return pattern;
}

// corruptPattern --> funzione che corrompe l'immagine in modo casuale
// Itera su tutti i pixel e, con probabilità noiseLevel, inverte il valore (+1 diventa -1 e viceversa). 
// Usa rand() con seed temporale.

std::vector<int> corruptPattern(const std::vector<int>& pattern, double noiseLevel) {
    //controllo che noiselevel sia compreso tra 0.0 e 1.0
    if (noiseLevel < 0.0 || noiseLevel > 1.0) {
        throw std::invalid_argument("corruptPattern: noiseLevel deve essere in [0.0, 1.0]");
    } 
 
    // Inizializza il generatore casuale (una sola volta per esecuzione)
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
 
    std::vector<int> corrupted = pattern; // copia dell'originale
 
    for (int& pixel : corrupted) {
        // Genera un numero in [0, 1) e confronta con noiseLevel
        double r = static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX) + 1.0);
        if (r < noiseLevel) {
            pixel = -pixel; // inversione del bit
        }
    }
 
    return corrupted;
}

 
// cutPattern
// Inverte tutti i pixel nella metà inferiore dell'immagine
// (righe da height/2 a height-1).
// Restituisce una copia; l'originale resta invariata.
std::vector<int> cutPattern(const std::vector<int>& pattern, int width, int height) {
 
    if (static_cast<int>(pattern.size()) != width * height) {
        throw std::invalid_argument("cutPattern: dimensioni width*height non corrispondono alla size del pattern");
    }
 
    std::vector<int> cut = pattern; // copia
 
    int halfStart = (height / 2) * width; // indice del primo pixel della metà inferiore
 
    for (int i = halfStart; i < width * height; ++i) {
        cut[i] = -cut[i]; // inversione
    }
 
    return cut;
}
 
// savePattern
// Costruisce una sf::Image di dimensioni width x height:
//   +1  ->  pixel bianco (255, 255, 255)
//   -1  ->  pixel nero   (  0,   0,   0)
// Poi salva l'immagine nel file indicato tramite sf::Image::saveToFile().
// L'estensione del filename determina il formato (es. ".png", ".bmp").
void savePattern(const std::vector<int>& pattern, int width, int height,
                 const std::string& filename) {
 
    if (static_cast<int>(pattern.size()) != width * height) {
        throw std::invalid_argument("savePattern: dimensioni width*height non corrispondono alla size del pattern");
    }
 
    sf::Image image;
    image.create(static_cast<unsigned int>(width),
                 static_cast<unsigned int>(height),
                 sf::Color::White);
 
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            sf::Color color = (pattern[idx] == +1) ? sf::Color::White : sf::Color::Black;
            image.setPixel(static_cast<unsigned int>(x),
                           static_cast<unsigned int>(y),
                           color);
        }
    }
 
    if (!image.saveToFile(filename)) {
        throw std::runtime_error("savePattern: impossibile salvare il file \"" + filename + "\"");
    }
}
