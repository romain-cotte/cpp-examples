
CC=g++
CFLAGS=-std=c++11 -Wall -g -posix

all: main

# Compile with boost library : -I/home/romain/lib/boost_1_57_0
compile:
	$(CC) $(CFLAGS) main.cpp -o main

main: compile
	./$@ | tee output.out

.PHONY: all main

