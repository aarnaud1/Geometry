CC := g++
IFLAGS := -I./include

all: clean bin/test_vec4f

bin/test_vec4f: tests/test_vec4f.cpp
	mkdir -p bin/
	$(CC) -std=c++11 -pedantic -O3 -g -o $@ $(IFLAGS) $^

clean:
	rm -f bin/*
