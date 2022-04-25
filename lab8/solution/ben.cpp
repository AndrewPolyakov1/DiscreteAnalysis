#include<iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "lib.h"

int main(){
    int M, N;
    int p;
    std::cin >> M >> N;
    std::vector<int_vector> coefs;
    int_vector cur;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N+1; j++){
            std::cin >> p;
            cur.push_back(p);
        }
        cur.push_back(i+1);
        coefs.push_back(cur);
        cur.clear();
    }
    std::cout << "GaussAlgorythm\n";

    {
        auto start = std::chrono::steady_clock::now();
        GaussAlgorythm(coefs, cur, N, M);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Time: " <<  elapsed_seconds.count() << std::endl;
    }
    std::cout << "Answer: ";
    if(cur.empty()){
        std::cout << -1 << std::endl;
    }
    else{
        std::sort(cur.begin(), cur.end());
        std::cout << *cur.begin();
        for(int_vector::iterator it = cur.begin() + 1; it != cur.end(); it++){
            std::cout << " " << *it;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "NaiveAlgorythm\n";
    std::pair<int_vector, int> respair;
    {
        auto start = std::chrono::steady_clock::now();
        int_vector freeplaces;
        for(int i = 0; i < M; i++){
            freeplaces.push_back(i);
        }
        respair = NaiveAlgorythm(freeplaces, N, 0, coefs);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Time: " <<  elapsed_seconds.count() << std::endl;
    }
    std::cout << "Answer: ";

    if(respair.first.empty()){
        std::cout << -1 << std::endl;
    }
    else{
        std::sort(respair.first.begin(), respair.first.end());
        std::cout << *respair.first.begin()+1;
        for(int_vector::iterator it = respair.first.begin() + 1; it != respair.first.end(); it++){
            std::cout << " " << *it + 1;
        }
        std::cout << std::endl;
    }
}