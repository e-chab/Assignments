#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    const char *filename = "input.txt";
    int homes, maxCandy;
    int *candy = NULL;
    int bestStart, bestEnd, bestSum;
    
    read_input(filename, &homes, &maxCandy, &candy);
    
    best_sequence(candy, homes, maxCandy, &bestStart, &bestEnd, &bestSum);

    print_result(bestStart, bestEnd, bestSum);
    
    free(candy);
}
