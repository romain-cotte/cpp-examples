
CC=g++
CFLAGS=-std=c++11 -Wall -g -posix

all: min-heap

# Compile with boost library : -I/home/romain/lib/boost_1_57_0
compile:
	$(CC) $(CFLAGS) min-heap.cpp -o min-heap

min-heap: compile
	./$@ | tee output.out

.PHONY: all min-heap
