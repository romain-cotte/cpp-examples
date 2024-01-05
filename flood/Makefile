CC=g++-8
WARNING_FLAGS=-Wall -Wno-deprecated-declarations -Wno-unused-result -Wfatal-errors
SANITIZE_FLAGS=-fno-sanitize-recover
CFLAGS=-std=c++17 -O0 $(WARNING_FLAGS) $(SANITIZE_FLAGS) -g -posix
LIBS=-lm -lcrypt -Iinclude -I/usr/local/include -lcurl -lcurlpp \
-I/home/romain/perso/cpp/rapidjson/include -L/usr/local/lib -lgdal


BIN=gdal

compile_main:
	$(CC) $(CFLAGS) -o main main.cpp $(LIBS)

compile_gdal:
	$(CC) $(CFLAGS) -o $(BIN) gdal.cpp $(LIBS)

debug:
	g++ -std=c++17 -Wshadow -Wall -g -fuse-ld=gold -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG main.cpp -o main

main: compile_main
	./main < main.in | tee main.out

gdal: compile_gdal
	./gdal

clean:
	rm -rf *.o main

.PHONY: main
