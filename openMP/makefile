all: test

trick_or_treat_brute_force.o: trick_or_treat_brute_force.cpp trick_or_treat_brute_force.h
	g++ -g -fopenmp -c trick_or_treat_brute_force.cpp -o trick_or_treat_brute_force.o

test: trick_or_treat_brute_force.o test.cpp
	g++ -g -fopenmp trick_or_treat_brute_force.o test.cpp -o test

benchmark: trick_or_treat_brute_force.o test_benchmark.cpp
	g++ -g -fopenmp trick_or_treat_brute_force.o test_benchmark.cpp -o benchmark -lbenchmark -lpthread