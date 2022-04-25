#include "biggest_int.hpp"
#include <gmpxx.h>

#include <iostream>
#include <vector>
#include <map>
#include <chrono>

using timeDuration = std::chrono::microseconds;

void GetTime(std::chrono::time_point<std::chrono::system_clock> & timeVar) {
    timeVar = std::chrono::system_clock::now();
}

int64_t CountTime(const std::chrono::time_point<std::chrono::system_clock> & start, const std::chrono::time_point<std::chrono::system_clock> & end) {
    return std::chrono::duration_cast<timeDuration>(end - start).count();
}

void printResults(std::map<char, int64_t> & myTime, std::map<char, int64_t> & gmpTime) {
    std::cout << "===============================" << std::endl;
    char op = '+';
    std::cout << "=====   ADDITION   =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    op = '-';
    std::cout << "=====  SUBTRACTION  =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    op = '*';
    std::cout << "===== MULTIPLICATION =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "    Karatsuba Time = " << myTime['K'] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    op = '/';
    std::cout << "=====    DIVISION    =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    op = '^';
    std::cout << "=====      POWER     =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    op = '<';
    std::cout << "=====    LESS THEN   =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    op = '=';
    std::cout << "=====    EQUAL TO    =====" << std::endl;
    std::cout << "  TBigInt_10e6 Time = " << myTime[op] << " ms" << std::endl;
    std::cout << "          GMP Time = " << gmpTime[op] << " ms" << std::endl;
    std::cout << "===============================" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    std::chrono::time_point<std::chrono::system_clock> myStart, myEnd, gmpStart, gmpEnd;
    std::map<char, int64_t> myTime;
    std::map<char, int64_t> gmpTime;
    std::vector<char> operations{ '+', '-', '*', '/', '<', '=' };
    for (char operation : operations) {
        myTime.insert(std::make_pair(operation, 0));
        gmpTime.insert(std::make_pair(operation, 0));
    }
    myTime.insert(std::make_pair('K', 0));

    std::string str1;
    std::string str2;
    char op;

    while(std::cin >> str1 >> str2 >> op) {
        NBiggestInt::TBigInt_10e6 num1(str1);
        NBiggestInt::TBigInt_10e6 num2(str2);
        mpz_class mpz1(str1);
        mpz_class mpz2(str2);

        try {
            if (op == '+') {

                GetTime(myStart);
                NBiggestInt::TBigInt_10e6 myRes = num1 + num2;
                GetTime(myEnd);

                GetTime(gmpStart);
                mpz_class gmpRes = mpz1 + mpz2;
                GetTime(gmpEnd);
                
            } else if (op == '-') {
                
                GetTime(myStart);
                NBiggestInt::TBigInt_10e6 myRes = num1 - num2;
                GetTime(myEnd);
                
                GetTime(gmpStart);
                mpz_class gmpRes = mpz1 - mpz2;
                GetTime(gmpEnd);
                
            } else if (op == '*') {
                
                GetTime(myStart);
                NBiggestInt::TBigInt_10e6 myRes = num1 * num2;
                GetTime(myEnd);
                myTime[op] += CountTime(myStart, myEnd);

                GetTime(myStart);
                NBiggestInt::TBigInt_10e6 karatsubaRes = NBiggestInt::TBigInt_10e6::KaratsubaMultiplication(std::move(num1), std::move(num2));
                GetTime(myEnd);
                myTime['K'] += CountTime(myStart, myEnd);

                GetTime(gmpStart);
                mpz_class gmpRes = mpz1 * mpz2;
                GetTime(gmpEnd);
                gmpTime[op] += CountTime(gmpStart, gmpEnd);

            } else if (op == '/') {

                GetTime(myStart);
                NBiggestInt::TBigInt_10e6 myRes = num1 / num2;
                GetTime(myEnd);

                GetTime(gmpStart);
                mpz_class gmpRes = mpz1 / mpz2;
                GetTime(gmpEnd);

            } else if (op == '^') {

                GetTime(myStart);
                NBiggestInt::TBigInt_10e6 myRes = num1.Pow(num2);
                GetTime(myEnd);

                mpz_class gmpRes;
                unsigned long int exp = std::stol(str2);
                GetTime(gmpStart);
                mpz_pow_ui(gmpRes.get_mpz_t(), mpz1.get_mpz_t(), exp);
                GetTime(gmpEnd);

            } else if (op == '<') {

                GetTime(myStart);
                bool myRes = num1 < num2;
                GetTime(myEnd);

                GetTime(gmpStart);
                bool gmpRes = mpz1 < mpz2;
                GetTime(gmpEnd);
                
            } else if (op == '=') {

                GetTime(myStart);
                bool myRes = num1 == num2;
                GetTime(myEnd);

                GetTime(gmpStart);
                bool gmpRes = mpz1 == mpz2;
                GetTime(gmpEnd);
            } else {
                std::cout << "Invalid operation" << "\n";
            }

            if (op != '*') {
                myTime[op] += CountTime(myStart, myEnd);
                gmpTime[op] += CountTime(gmpStart, gmpEnd);
            }

        } catch (const std::exception & exp) {
            continue;
        }
    }

    printResults(myTime, gmpTime);

    return 0;
}