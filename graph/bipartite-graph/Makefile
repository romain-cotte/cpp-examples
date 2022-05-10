PB=C

CC=g++
CFLAGS=-std=c++17 -pthread -O0 -Wshadow -Wall -g -posix -Wfatal-errors -Wno-unused-result

all: c

compare:
	./main < main.in | tee main.out
	./test < main.in | tee test.out

c:
	$(CC) $(CFLAGS) main.cpp -o main

debug:
	g++ -std=c++14 -Wshadow -Wall -o main main.cpp -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
	./main < main.in

compile_main:
	$(CC) $(CFLAGS) main.cpp -o main

compile_other:
	$(CC) $(CFLAGS) other.cpp -o other

compile_gen:
	$(CC) $(CFLAGS) gen.cpp -o gen

compile_test:
	$(CC) $(CFLAGS) test.cpp -o test

compile_example:
	$(CC) $(CFLAGS) $(CPP_DIR)/example.cpp -o $(BUILD_DIR)/example

test: compile_test
	./test < test.in | tee test.out

main: c
	./main < main.in | tee main.out

gen: compile_gen
	./gen | tee gen.out

.PHONY: main, sample
