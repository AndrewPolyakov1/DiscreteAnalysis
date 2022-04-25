#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include "SuffTree.h"
#include <chrono>

using duration_t = std::chrono::microseconds;
int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int res_time = 0;
    start = std::chrono::system_clock::now();
    //std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::string pattern1, pattern2;
    std::cin >> pattern1 >> pattern2;
    TSuffixTree st(pattern1, pattern2);
    end = std::chrono::system_clock::now();
    res_time += std::chrono::duration_cast<duration_t>( end - start ).count();
    std::cout << "Time: " << res_time << "*10^-6 seconds" <<'\n'; 
    st.DisplayTree();
    return 0;
}