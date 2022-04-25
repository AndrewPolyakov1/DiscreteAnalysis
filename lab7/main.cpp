#include "lib.h"

int main() {
    int n;
    std::cin >> n;

    int* arr = new int[n + 1];
    int value = MinPath(arr, n);
	std::cout << value << std::endl;
    ReconstructPath(arr, n);

    delete[] arr;
    return 0;
}