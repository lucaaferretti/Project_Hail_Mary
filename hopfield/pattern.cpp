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
 
    // --- Ridimensionamento tramite RenderTexture ---
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
 
    // --- Conversione pixel -> {+1, -1} ---
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
//(void) serve per non far dare errore al compilatore
//return{} serve per restituire un vettore int come da dichiarazione
//ma vuoto

std::vector<int> corruptPattern(const std::vector<int>& pattern, double noiseLevel) {
   
    (void)noiseLevel;
    return pattern;
}
//si ritorna pattern per non far crashare il programma

std::vector<int> cutPattern(const std::vector<int>& pattern, int width, int height) {
    
    (void)width;
    (void)height;
    return pattern;
}

void savePattern(const std::vector<int>& pattern, int width, int height,
                 const std::string& filename) {
   
    (void)pattern;
    (void)width;
    (void)height;
    (void)filename;
}
