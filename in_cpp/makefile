all: test

trick_or_treat.o: trick_or_treat.cpp trick_or_treat.h
	g++ -c trick_or_treat.cpp -o trick_or_treat.o 

test: trick_or_treat.o test.cpp
	g++ trick_or_treat.o test.cpp -o test

benchmark: trick_or_treat.o test_benchmark.cpp
	g++ trick_or_treat.o test_benchmark.cpp -o benchmark -lbenchmark -lpthread
