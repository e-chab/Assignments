#ifndef TRICK_OR_TREAT_H
#define TRICK_OR_TREAT_H

#include <vector>
#include <string>

bool read_input(const std::string &filename, int &homes, int &maxCandy, std::vector<int> &candy);
bool best_sequence(const std::vector<int> &candy, int homes, int maxCandy, int &bestStart, int &bestEnd, int &bestSum);
void print_result(int bestStart, int bestEnd, int bestSum);

#endif
