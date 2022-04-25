CC = g++

CFLAGS = --std=c++17 -c -Wall -Werror -Wextra -O3

DEBUG = --std=c++17 -c -g -Wall

all: solution

solution: graph.o main.o
	$(CC) graph.o main.o -o solution

graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp -o graph.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -rf *.o solution