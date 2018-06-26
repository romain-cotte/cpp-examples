CC=g++
CFLAGS=-std=c++11 -Wall -posix

all: main

compile:
	$(CC) -g main.cpp -o main $(CFLAGS)

main: compile
	./$@ | tee $@.out

test:
	./main | tee main.out

.PHONY: main

