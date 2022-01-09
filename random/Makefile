PB=A

CC=g++
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
# SANITIZE_FLAGS=-fsanitize=undefined -fno-sanitize-recover
SANITIZE_FLAGS=
CFLAGS=-std=c++17 -O3 $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix

all: c

compile:
	$(CC) $(PB).cpp $(CFLAGS) -o $(PB)

# g++ -std=c++17 -O2 -Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors  -g -posix main.cpp -o main
c:
	$(CC) main.cpp $(CFLAGS) -o main

debug:
	g++ -std=c++17 -Wshadow -Wall -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG main.cpp -o main
	./main < main.in

debug_test:
	g++ -std=c++17 -Wshadow -Wall -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG test.cpp -o main
	./test < test.in

compile_test:
	$(CC) test.cpp $(CFLAGS) -o test

compile_other:
	$(CC) $(CFLAGS) other.cpp -o other

compile_gen:
	$(CC) $(CFLAGS) gen.cpp -o gen

sample: compile
	./$(PB) < $(PB)-$@.in | tee $(PB)-$@.out

small: compile
	./$(PB) < $(PB)-$@.in | tee $(PB)-$@.out

large: compile
	./$(PB) < $(PB)-$@.in | tee $(PB)-$@.out

test: compile_test
	./test < test.in | tee test.out

other: compile_other
	./other < other.in | tee other.out

gen: compile_gen
	./gen | tee gen.out

main: c
	./main < main.in | tee main.out

m:
	./main < main.in | tee main.out

python:
	python3 main.py < main.in | tee main.out

clean:
	rm -rf *.o other main

.PHONY: main sample gen
