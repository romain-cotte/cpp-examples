CC=g++
CXXFLAGS=-std=c++11 -Wall -g -posix -Wfatal-errors

BIN=main

execute:
	./$(BIN) | tee $(BIN).out

compile:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp -o $(BIN)

main: compile
	./$(BIN) | tee $(BIN).out

.PHONY: main

clean:
	rm -rf *o main
