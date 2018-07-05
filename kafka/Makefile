CC=gcc

INCLUDE=-I../include
CXXFLAGS=-std=c++11 -Wall -g -posix -Wfatal-errors -lz -lpthread -lrt $(INCLUDE)
KAFKAFLAGS=-lrdkafka++ -lrdkafka -lstdc++

BIN=main
BIN_OR=main_or

execute:
	./$(BIN) | tee $(BIN).out

vector.o: ../util/vector.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

assert.o: ../util/assert.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

main_or.o: main_or.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

compile_or: vector.o assert.o main_or.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(KAFKAFLAGS) -o $(BIN_OR)

compile: vector.o assert.o main.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(KAFKAFLAGS) -o $(BIN)

consumer_compile: vector.o assert.o consumer.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(KAFKAFLAGS) -o consumer

kafka_consumer_compile: vector.o assert.o kafka_consumer.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(KAFKAFLAGS) -o kafka_consumer

main_or: compile_or
	./$@ -C -p 0 -t test

main: compile
	./$(BIN) | tee $(BIN).out

consumer: consumer_compile
	./$@ | tee $(BIN).out

kafka_consumer: kafka_consumer_compile
	./$@ | tee $@.out

.PHONY: main

clean:
	rm -rf *.o main

