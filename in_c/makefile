all: test_main

trick_or_treat.o: trick_or_treat.c trick_or_treat.h
	gcc -c trick_or_treat.c -o trick_or_treat.o

test_main: trick_or_treat.o test_main.c
	gcc trick_or_treat.o test_main.c -o test_main

