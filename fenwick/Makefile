
CC=g++
CFLAGS=-std=c++17 -Wall -g

all: main

# Compile with boost library : -I/home/romain/lib/boost_1_57_0
compile:
	$(CC) $(CFLAGS) main.cpp -o main

main: compile
	./$@ | tee output.out


ex2:
	$(CC) $(CFLAGS) ex2.cpp -o ex2
	./ex2

.PHONY: all main ex2

