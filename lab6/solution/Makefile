CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wno-unused-variable -O3
LDFLAGS = 

EXECUTABLE = solution
DEBUG_EXE  = debug.out
BENCH_EXE  = benchmark
TEST       = unit_test

EXE_SRC = main.cpp long_arythmetics.cpp
EXE_OBJ = $(EXE_SRC:.cpp=.o)

BENCH_SRC = benchmark.cpp long_arythmetics.cpp
BENCH_OBJ = $(BENCH_SRC:.cpp=.o)

TEST_SRC = unit_tests.cpp long_arythmetics.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all : $(EXECUTABLE)

debug : CXXFLAGS += -g -fsanitize=address
debug : EXECUTABLE = $(DEBUG_EXE)
debug : $(EXECUTABLE)

benchmark : CXXFLAGS += -lgmp -lgmpxx
benchmark : $(BENCH)

test : LD_FLAGS += -lgtest -lgtest_main
test : $(TEST)

$(EXECUTABLE) : $(EXE_OBJ)
	$(CXX) $(CXXFLAGS) $(EXE_OBJ) -o $(EXECUTABLE)

$(BENCH_EXE) : $(BENCH_OBJ)
	$(CXX) $(CXXFLAGS) $(BENCH_OBJ) -o $(BENCH_EXE)

$(TEST) : $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST) $(LD_FLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) $(DEBUG_EXE) $(BENCH_EXE) $(TEST)