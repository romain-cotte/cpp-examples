CC=g++
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
SANITIZE_FLAGS=-fno-sanitize-recover
CFLAGS=-std=c++20 -D DEBUG_LOCAL=true -O2 $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix
LIBS=-lm -lcrypt


all: main

# compile:
# 	$(CC) -g main.cpp -o main $(CFLAGS)

# main: compile
# 	./$@ | tee $@.out

ex1 ex2 ex3 ex4 ex5 ex6:
	$(CC) -g $@.cpp -o $@ $(CFLAGS)
	./$@ | tee $@.out

.PHONY: main ex1 ex2 ex3 ex4 ex5 ex6



# ifdef DEBUG -> -D DEBUG

BIN=main

compile_main:
	$(CC) $(CFLAGS) -o $(BIN) main.cpp $(LIBS)

debug:
	g++ -std=c++17 -Wshadow -Wall -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG main.cpp -o main

main: compile_main


clean:
	rm -rf *.o main

.PHONY: main
