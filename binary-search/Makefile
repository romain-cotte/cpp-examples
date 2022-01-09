CC=g++
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
SANITIZE_FLAGS=-fno-sanitize-recover
CFLAGS=-std=c++17 -O2 $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix
LIBS=-lm -lcrypt
# ifdef DEBUG -> -D DEBUG

BIN=main

# main: compile_main
# 	./main < main.in | tee main.out

compile_main:
	$(CC) $(CFLAGS) -o $(BIN) main.cpp $(LIBS)

debug:
	g++ -std=c++17 -O2 $(WARNING_FLAGS) $(DEBUG_FLAGS) main.cpp -o main


clean:
	rm -rf *.o main

.PHONY: main
