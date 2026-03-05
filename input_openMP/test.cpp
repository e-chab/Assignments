#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <omp.h>

#include "trick_or_treat_input_optimized.h"

int main(int argc, char** argv) {
    std::string filename = (argc >= 2) ? argv[1] : "../input_10000_pirecas.txt";
    int threads = (argc > 2) ? std::atoi(argv[2]) : 4;

    omp_set_num_threads(threads);

    int homes, maxCandy;
    std::vector<int> candy;
    int bestStart, bestEnd, bestSum;

    auto start_time = std::chrono::high_resolution_clock::now();

    read_input_openmp(filename, homes, maxCandy, candy);

    best_sequence(candy, homes, maxCandy, bestStart, bestEnd, bestSum);

    print_result(bestStart, bestEnd, bestSum);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "\n=== RESULTS ===\n";
    std::cout << "File: " << filename << "\n";
    std::cout << "Homes: " << homes << "\n";
    std::cout << "Max candy: " << maxCandy << "\n";
    std::cout << "Threads: " << threads << "\n";
    std::cout << "Result: Start=" << (bestStart + 1) 
              << ", End=" << (bestEnd + 1) 
              << ", Sum=" << bestSum << "\n";
    std::cout << "Total time: " << elapsed_ms << " ms\n";
}
