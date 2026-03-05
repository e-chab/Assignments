// trick_or_treat_parallel.h
#pragma once

#include <vector>
#include <string>

// Lit le fichier d'entrée et remplit le vecteur candy
bool read_input(const std::string &filename, int &homes, int &maxCandy, std::vector<int> &candy);

// Résout le problème avec la version brute-force OpenMP parallélisée
bool best_sequence_parallel(const std::vector<int> &candy, int homes, int maxCandy,
                            int &bestStart, int &bestEnd, int &bestSum);

// Affiche le résultat
void print_result(int bestStart, int bestEnd, int bestSum);