
CC=g++
CFLAGS=-std=c++11 -Wall -posix

all: main

# Compile with boost library : -I/home/romain/lib/boost_1_57_0
compile:
	$(CC) -g main.cpp -o main $(CFLAGS)

main: compile
	./$@ | tee output.out

test:
	./main | tee output.out

.PHONY: all main
