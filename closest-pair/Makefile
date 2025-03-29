CC=g++
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
SANITIZE_FLAGS=-fno-sanitize-recover
CFLAGS=-std=c++20 -O0 -D DEBUG_LOCAL=true -D COLOR=true $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix
LIBS=-lm -lcrypt
# ifdef DEBUG -> -D DEBUG

BIN=main

compile_main:
	$(CC) $(CFLAGS) -o $(BIN) main.cpp $(LIBS)

compile_gen:
	$(CC) $(CFLAGS) -o gen gen.cpp $(LIBS)

debug:
	g++ -std=c++20 -Wshadow -Wall -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG main.cpp -o main

main: compile_main
	./main < main.in | tee main.out

gen: compile_gen
	./gen

clean:
	rm -rf *.o main gen

.PHONY: main gen
