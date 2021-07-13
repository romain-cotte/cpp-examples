CC=g++

INCLUDE=-I../include
CXXFLAGS=-std=c++11 -Wall -g -Wfatal-errors $(INCLUDE)

BIN=main

execute:
	./$(BIN) | tee $(BIN).out

vector.o: ../util/vector.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

assert.o: ../util/assert.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

compile: vector.o assert.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ main.cpp -o $(BIN)

main: compile


.PHONY: main

clean:
	rm -rf *.o main
