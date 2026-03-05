#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <omp.h> 

#include "trick_or_treat_brute_force.h"

int main(int argc, char** argv) {

    if (argc >= 2) {
        int num_threads = std::atoi(argv[1]);
        omp_set_num_threads(num_threads);
    }
    std::string filename = (argc >= 3) ? argv[2] : "../input_10000_pirecas.txt";
    
    int homes, maxCandy;
    std::vector<int> candy;
    int bestStart, bestEnd, bestSum;

    auto start_time = std::chrono::high_resolution_clock::now();

    read_input(filename, homes, maxCandy, candy);

    best_sequence_parallel(candy, homes, maxCandy, bestStart, bestEnd, bestSum);

    print_result(bestStart, bestEnd, bestSum);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "\n=== RESULTS ===\n";
    std::cout << "File: " << filename << "\n";
    std::cout << "Homes: " << homes << "\n";
    std::cout << "Max candy: " << maxCandy << "\n";
    std::cout << "Result: Start=" << (bestStart + 1) 
              << ", End=" << (bestEnd + 1) 
              << ", Sum=" << bestSum << "\n";
    std::cout << "Total time: " << elapsed_ms << " ms\n";
}
