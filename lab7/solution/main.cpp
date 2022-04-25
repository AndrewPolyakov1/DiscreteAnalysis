#include "lib.h"

int main() {
    int n;
    std::cin >> n;

    int* input = new int[n + 1];
    int value = MinPath(input, n);
	std::cout << value << std::endl;
    ReconstructPath(input, n);

    delete[] input;
    return 0;
}