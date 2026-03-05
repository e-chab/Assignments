#include <benchmark/benchmark.h>
#include "trick_or_treat.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

// Create a random temporary file
static std::string CreateRandomFile(int size) {
    std::string filename = "benchmark.txt";
    
    std::ofstream file(filename);
    
    // Write the number of homes
    file << size << "\n";
    
    // Write random data (the first one is maxCandy)
    for (int i = 0; i < size + 1; ++i) {
        file << (rand() % 1001) << "\n";  // 0 to 1000
    }
    
    file.close();
    return filename;
}

// Benchmark 1: Only file reading
static void BM_ReadInput(benchmark::State& state) {
    int size = state.range(0);
    std::string filename = CreateRandomFile(size);  // Create the file once
    int homes, maxCandy;
    std::vector<int> candy;
    
    for (auto _ : state) {
        read_input(filename, homes, maxCandy, candy);
        benchmark::DoNotOptimize(homes);
        benchmark::DoNotOptimize(candy);
    }
    
    // Clean up the file
    remove(filename.c_str());
}

// Benchmark 2: Only best_sequence computation (data loaded before the loop)
static void BM_BestSequence(benchmark::State& state) {
    int size = state.range(0);
    std::string filename = CreateRandomFile(size);  
    int homes, maxCandy;
    std::vector<int> candy;
    read_input(filename, homes, maxCandy, candy);
    int bestStart, bestEnd, bestSum;
    
    for (auto _ : state) {
        best_sequence(candy, homes, maxCandy, bestStart, bestEnd, bestSum);
        
        benchmark::DoNotOptimize(bestStart);
        benchmark::DoNotOptimize(bestEnd);
        benchmark::DoNotOptimize(bestSum);
    }

    remove(filename.c_str());
}

// Benchmark 3: Full pipeline (read + best_sequence + print_result)
static void BM_FullPipeline(benchmark::State& state) {
    int size = state.range(0);
    std::string filename = CreateRandomFile(size);  
    int homes, maxCandy;
    std::vector<int> candy;
    int bestStart, bestEnd, bestSum;
    
    for (auto _ : state) {
        
        read_input(filename, homes, maxCandy, candy);
        
        best_sequence(candy, homes, maxCandy, bestStart, bestEnd, bestSum);
        
        //print_result(bestStart, bestEnd, bestSum);
        
        benchmark::DoNotOptimize(bestStart);
        benchmark::DoNotOptimize(bestEnd);
        benchmark::DoNotOptimize(bestSum);
    }
    
    // Clean up the file
    remove(filename.c_str());
}



BENCHMARK(BM_ReadInput)
    ->Arg(100)->Arg(1000)->Arg(5000)->Arg(10000)
    ->Repetitions(20)  // Repeat 20 times
    ->DisplayAggregatesOnly(true);  // Display only aggregated statistics

BENCHMARK(BM_BestSequence)
    ->Arg(100)->Arg(1000)->Arg(5000)->Arg(10000)
    ->Repetitions(20)
    ->DisplayAggregatesOnly(true);

BENCHMARK(BM_FullPipeline)
    ->Arg(100)->Arg(1000)->Arg(5000)->Arg(10000)
    ->Repetitions(20)
    ->DisplayAggregatesOnly(true);

BENCHMARK_MAIN();