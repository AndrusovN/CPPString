CC=g++
CFLAGS=-Wall -Wextra -Wpedantic -Werror
SOURCES=main.cpp
OUTPUT=main

build: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT).o

clean:
	rm -rf $(OUTPUT).o
