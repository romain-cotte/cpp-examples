CC=g++
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
DEBUG_FLAGS=-fuse-ld=gold -fsanitize=address -static-libasan -fsanitize=undefined -D_GLIBCXX_DEBUG
CFLAGS=-std=c++17 -O2 $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix
LIBS=-lm -lcrypt

BIN=main

compile_main:
	$(CC) $(CFLAGS) -o $(BIN) main.cpp $(LIBS)

debug:
	g++ -std=c++17 -O2 $(WARNING_FLAGS) $(DEBUG_FLAGS) main.cpp -o main

main: compile_main
	./main < main.in | tee main.out

clean:
	rm -rf *.o main

.PHONY: main
