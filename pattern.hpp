#ifndef PATTERN_HPP
#define PATTERN_HPP
 
#include <vector>
#include <string>
 

std::vector<int> loadPattern(const std::string& filename, int targetN);
//serve a restituire i valori(+-1) del pattern a partire
//dal file immagine passato per riferimento costante
//int targetN è il numero di pixel dell'immaigne dopo
//il ridimensionamento

std::vector<int> corruptPattern(const std::vector<int>& pattern, double noiseLevel);
//ha come parametri il pattern passato per riferimento costante e 
//il noiseLevel che è la percentuale di pixel da invertire
//restituisce una copia corretta, l'originale rimane invariata
//per vi del const
 
std::vector<int> cutPattern(const std::vector<int>& pattern, int width, int height);
//serve a invertire la metà inferiore del pattern, restituisce una 
//copia corrotta diversa dalla dichiarazione precedente

void savePattern(const std::vector<int>& pattern, int width, int height, const std::string& filename);
//salva il patten sul file di destinazione

#endif
