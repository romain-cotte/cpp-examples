
CC=g++
EIGENFLAG=$(shell pkg-config --cflags eigen3)
CFLAGS=-std=c++11 -Wall -g -posix $(EIGENFLAG)

all: compile
	./main

compile:
	$(CC) $(CFLAGS) main.cpp -o main
