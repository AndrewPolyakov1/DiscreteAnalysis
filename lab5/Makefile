CC=g++

FLAGS =  -pedantic  -std=c++17 -g -Ofast -Wextra -Werror -no-pie

all: suffixTree.cpp suffixTree.hpp main.cpp
	g++ $(FLAGS) suffixTree.cpp main.cpp -o solution

clean:
	rm -rf *.o solution