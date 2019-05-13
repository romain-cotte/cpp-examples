CC=g++

INCLUDE=-I../include
CXXFLAGS=-std=c++11 -Wall -g -posix -Wfatal-errors $(INCLUDE)

BIN=main

main: compile
	./$(BIN) | tee $(BIN).out

execute:
	./$(BIN) | tee $(BIN).out

vector.o: ../util/vector.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

assert.o: ../util/assert.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

compile: vector.o assert.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ main.cpp -o $(BIN)



.PHONY: main

clean:
	rm -rf *.o main
