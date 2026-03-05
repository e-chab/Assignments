# Implementation OpenMP - Parallel Brute Force

This directory contains a parallel implementation of the trick-or-treat problem using OpenMP with brute-force algorithm.

## Files

- **`trick_or_treat_brute_force.cpp/h`** : OpenMP parallel implementation with O(n²) brute-force algorithm
- **`test.cpp`** : Simple test program with configurable thread count
- **`test_benchmark.cpp`** : Google Benchmark suite for parallel performance analysis
- **`plot_speedup.py`** : Python script to measure and visualize speedup across thread counts

## Usage

### Simple test
```bash
make test
./test [threads] [input_file]
```

### Benchmark
```bash
make benchmark
./benchmark
```

Tests different thread counts (1, 2, 4, 8, 16) on various input sizes.

### Speedup analysis
```bash
python3 plot_speedup.py --input ../input_10000_pirecas.txt 
```

Generates speedup graphs (time, speedup, efficiency).

Default: 4 threads, `../input_10000_pirecas.txt`
