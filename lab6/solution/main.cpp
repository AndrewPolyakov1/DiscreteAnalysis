#include <iostream>
#include <vector>
#include "long_arythmetics.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string str1, str2;
    std::string op;

    while(std::cin >> str1 >> str2 >> op) {
        try {
            BigInt_e6::TBigInt_e6 num1(str1);
            BigInt_e6::TBigInt_e6 num2(str2);
            if (op == "+") {
                std::cout << num1 + num2 << "\n";
            } else if (op == "-") {
                std::cout << num1 - num2 << "\n";
            } else if (op == "*") {
                std::cout << num1 * num2 << "\n";
            } else if (op == "/") {
                std::cout << num1 / num2 << "\n";
            } else if (op == "^") {
                std::cout << num1.Power(num2) << "\n";
            } else if (op == "<") {
                std::cout << ( (num1 < num2) ? "true" : "false" ) << "\n";
            } else if (op == ">") {
                std::cout << ( (num1 > num2) ? "true" : "false" ) << "\n";
            } else if (op == "=") {
                std::cout << ( (num1 == num2) ? "true" : "false" ) << "\n";
            } else {
                std::cout << "Invalid operation" << "\n";
            }
        } catch (const std::exception & exp) {
            std::cout << "Error" << "\n";
        } 
    }
    return 0;
}