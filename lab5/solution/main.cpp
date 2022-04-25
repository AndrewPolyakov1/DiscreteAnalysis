#include "SuffTree.h"

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string pattern1, pattern2;
    std::cin >> pattern1 >> pattern2;
    TSuffixTree st(pattern1, pattern2);

    return 0;
}