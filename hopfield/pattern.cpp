#include "pattern.hpp"

#include <stdexcept>

std::vector<int> loadPattern(const std::string& filename, int targetN) {
   
    (void)filename;
    (void)targetN;
    return {};
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