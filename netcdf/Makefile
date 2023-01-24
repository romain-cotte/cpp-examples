CC=g++
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
SANITIZE_FLAGS=-fno-sanitize-recover
CFLAGS=-std=c++17 -O2 $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial
# -I/home/romain/programs/cpp-lib/netcdf/netcdf-cxx4-4.3.1/build/cxx4

LIBS=-lnetcdf -lhdf5_hl -lhdf5 -lpthread -lsz -lz -ldl -lm -lcurl
# ifdef DEBUG -> -D DEBUG

BIN=main

compile_main:
	$(CC) $(CFLAGS) -o $(BIN) main.cpp $(LIBS)

debug:
	g++ -std=c++17 -Wshadow -Wall -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG main.cpp -o main

main: compile_main
	./main < main.in | tee main.out

clean:
	rm -rf *.o main

.PHONY: main
