
CC=g++
CFLAGS=-std=c++11 -Wall -g -posix
BFLAGS=-lboost_system -lboost_thread -lpthread

sync_timer: sync_timer.o
	$(CC) -o sync_timer sync_timer.o $(BFLAGS)

sync_timer.o: sync_timer.cpp
	$(CC) -c sync_timer.cpp

clean:
	rm -f *.o sync_timer
