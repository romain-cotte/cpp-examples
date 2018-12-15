CC=g++

INCLUDE=-I../include -lcrypto -ljwt
CXXFLAGS=-std=c++11 -Wall -g -posix -Wfatal-errors

BIN=main

execute:
	./$(BIN) | tee $(BIN).out

vector.o: ../util/vector.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

assert.o: ../util/assert.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

compile: vector.o assert.o
	$(CXX) $^  $(CPPFLAGS) $(CXXFLAGS) main.cpp $(INCLUDE) -o $(BIN)

main: compile
	./$(BIN) | tee $(BIN).out

.PHONY: main

clean:
	rm -rf *.o main
