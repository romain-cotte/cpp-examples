CC=gcc

INCLUDE=-I../include
CXXFLAGS=-Wall -g -posix -Wfatal-errors -lz -lpthread -lrt $(INCLUDE)
KAFKAFLAGS=-lrdkafka++ -lrdkafka -lstdc++

BIN=main

execute:
	./$(BIN) | tee $(BIN).out

vector.o: ../util/vector.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

assert.o: ../util/assert.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

compile: vector.o assert.o main.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(KAFKAFLAGS) -o $(BIN)

consumer_compile:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ consumer.cpp -o $(BIN)

main: compile
	./$(BIN) | tee $(BIN).out

consumer: consumer_compile
	./$@ | tee $(BIN).out

.PHONY: main

clean:
	rm -rf *.o main
