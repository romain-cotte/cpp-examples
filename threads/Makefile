CC=g++
CFLAGS=-std=c++11 -pthread -Wall -posix

all: main

compile:
	$(CC) -g main.cpp -o main $(CFLAGS)

main: compile
	./$@ | tee $@.out

ex1 ex2 ex3 ex4 ex5 ex6:
	$(CC) -g $@.cpp -o $@ $(CFLAGS)
	./$@ | tee $@.out

.PHONY: main ex1 ex2 ex3 ex4 ex5 ex6
