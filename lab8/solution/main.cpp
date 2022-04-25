#include <algorithm>
#include <iostream>
#include <vector>

#include "lib.h"

int main() {
    int M, N;
    int p;
    std::cin >> M >> N;
    std::vector<doub_vector> coefficient;
    doub_vector current;

	// Fill vectors with input values
    for (int i = 0; i < M; i++) {
	   for (int j = 0; j < N + 1; j++) {
		  std::cin >> p;
		  current.push_back(p);
	   }
	   current.push_back(i + 1);
	   coefficient.push_back(current);
	   current.clear();
    }

	// 
    GaussAlgorythm(coefficient, current, N, M);

	// Print results
    if (current.empty()) {
	   std::cout << -1 << std::endl;

    } else {
	   std::sort(current.begin(), current.end());
	   std::cout << *current.begin();

	   for (doub_vector::iterator it = current.begin() + 1; it != current.end(); it++) {
		  std::cout << " " << *it;
	   }

	   std::cout << std::endl;
    }
}