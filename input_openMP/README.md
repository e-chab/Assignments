# Parallelization Experiments

This directory contains experiments with parallelizing input reading using OpenMP.

## Files

- **`trick_or_treat_input_optimized.cpp/h`** : Implementation with parallel input filling
- **`test.cpp`** : Test program
- **`makefile`** : Build configuration

## Usage

```bash
make
./test [input_file]
```

Default: `../input_10000_pirecas.txt`

Try trick_or_treat_input_optimized.cpp with either int temp[10000]; or std::vector<int> temp(homes);
