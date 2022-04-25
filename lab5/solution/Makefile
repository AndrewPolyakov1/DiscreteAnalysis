CC=g++

FLAGS =  -pedantic  -std=c++17 -g -Ofast -Wextra -Werror -no-pie

all: SuffTree.cpp SuffTree.h main.cpp
	g++ $(FLAGS) SuffTree.cpp main.cpp -o solution

clean:
	rm -rf *.o solution