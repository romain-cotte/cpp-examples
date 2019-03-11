
CC=g++
CFLAGS=-std=c++17 -Wall -g -posix

all: main

# Compile with boost library : -I/home/romain/lib/boost_1_57_0
compile:
	$(CC) $(CFLAGS) main.cpp -o main

main: compile
	./$@ < main.in | tee main.out

.PHONY: all main

