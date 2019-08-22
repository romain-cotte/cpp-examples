CC=g++
CFLAGS=-std=c++11 -Wall -g -posix

all: main

compile:
	$(CC) $(CFLAGS) main.cpp -o main

main: compile
	./$@ | tee output.out

.PHONY: all main

