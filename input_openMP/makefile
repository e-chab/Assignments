all: test

trick_or_treat_input_optimized.o: trick_or_treat_input_optimized.cpp trick_or_treat_input_optimized.h
	g++ -g -fopenmp -c trick_or_treat_input_optimized.cpp -o trick_or_treat_input_optimized.o

test: trick_or_treat_input_optimized.o test.cpp
	g++ -g -fopenmp trick_or_treat_input_optimized.o test.cpp -o test
