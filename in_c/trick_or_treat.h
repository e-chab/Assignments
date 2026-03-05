#ifndef TRICK_OR_TREAT_H
#define TRICK_OR_TREAT_H

int read_input(const char *filename, int *homes, int *maxCandy, int **candy);
int best_sequence(int *candy, int homes, int maxCandy, int *bestStart, int *bestEnd, int *bestSum);
void print_result(int bestStart, int bestEnd, int bestSum);

#endif