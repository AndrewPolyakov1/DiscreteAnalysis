CC=g++
CFLAGS=-std=c++14 -pedantic -Wall
EXECUTABLE=solution
SRC=main.cpp sort.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

sort.cpp: sort.hpp

main.o: sort.hpp vector.hpp

clean:
	rm -f *.o