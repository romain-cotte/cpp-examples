
CC=g++
CFLAGS=-std=c++11 -Wall -g -posix
BFLAGS=-lboost_system -lboost_thread -lpthread

sync_timer: sync_timer.o
	$(CC) -o sync_timer sync_timer.o $(BFLAGS)

sync_timer.o: sync_timer.cpp
	$(CC) -c sync_timer.cpp $(CFLAGS)

steady_timer: steady_timer.o
	$(CC) -o steady_timer steady_timer.o $(BFLAGS)

steady_timer.o: steady_timer.cpp
	$(CC) -c steady_timer.cpp $(CFLAGS)

threads: threads.o
	$(CC) -o threads threads.o $(BFLAGS)

threads.o: threads.cpp
	$(CC) -c threads.cpp $(CFLAGS)

async_timer: async_timer.o
	$(CC) -o async_timer async_timer.o $(BFLAGS)

async_timer.o: async_timer.cpp
	$(CC) -c async_timer.cpp


clean:
	rm -f *.o sync_timer
