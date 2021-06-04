CXX = g++
CXXFLAGS = -std=c++17 -O2 -g -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp
NAME = solution

all: example

example:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME)