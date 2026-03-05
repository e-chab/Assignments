#include <benchmark/benchmark.h>
#include "trick_or_treat_brute_force.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

// Create a random temporary file
static std::string CreateRandomFile(int size) {
    std::string filename = "benchmark.txt";
    std::ofstream file(filename);

    // Write the header
    file << size << "\n";

    // Write random data (the first one written is maxCandy)
    for (int i = 0; i < size + 1; ++i) {
        file << (rand() % 1001) << "\n";  // 0 to 1000
    }

    file.close();
    return filename;
}

// Benchmark 1: Only best_sequence_parallel computation
// Parameters: range(0)=number of threads, range(1)=input size
static void BM_BestSequenceParallel(benchmark::State& state) {
    int numThreads = state.range(0);
    int size = state.range(1);

    omp_set_num_threads(numThreads);

    std::string filename = CreateRandomFile(size);  
    
    int homes, maxCandy;
    std::vector<int> candy;
    int bestStart, bestEnd, bestSum;

    for (auto _ : state) {
        best_sequence_parallel(candy, homes, maxCandy, bestStart, bestEnd, bestSum);

        benchmark::DoNotOptimize(bestStart);
        benchmark::DoNotOptimize(bestEnd);
        benchmark::DoNotOptimize(bestSum);
    }

    remove(filename.c_str());
}

// Benchmark 2: Full pipeline (read + best_sequence_parallel + print_result)
static void BM_FullPipelineParallel(benchmark::State& state) {
    int numThreads = state.range(0);
    int size = state.range(1);

    omp_set_num_threads(numThreads);

    int homes, maxCandy;
    std::vector<int> candy;
    int bestStart, bestEnd, bestSum;

    std::string filename = CreateRandomFile(size);  

    for (auto _ : state) {
        read_input(filename, homes, maxCandy, candy);
        best_sequence_parallel(candy, homes, maxCandy, bestStart, bestEnd, bestSum);
        // print_result(bestStart, bestEnd, bestSum);

        benchmark::DoNotOptimize(bestStart);
        benchmark::DoNotOptimize(bestEnd);
        benchmark::DoNotOptimize(bestSum);
    }

    remove(filename.c_str());
}

// Register benchmarks
// BestSequenceParallel for threads 1,2,4,8,16 and sizes 100,1000,10000
BENCHMARK(BM_BestSequenceParallel)
    ->Args({1, 100})->Args({2, 100})->Args({4, 100})->Args({8, 100})->Args({16, 100})
    ->Args({1, 1000})->Args({2, 1000})->Args({4, 1000})->Args({8, 1000})->Args({16, 1000})
    ->Args({1, 10000})->Args({2, 10000})->Args({4, 10000})->Args({8, 10000})->Args({16, 10000})
    ->Repetitions(20)
    ->DisplayAggregatesOnly(true);

// FullPipelineParallel for 4 threads and sizes 100,1000,10000
BENCHMARK(BM_FullPipelineParallel)
    ->Args({4, 100})->Args({4, 1000})->Args({4, 10000})
    ->Repetitions(20)
    ->DisplayAggregatesOnly(true);

BENCHMARK_MAIN();
