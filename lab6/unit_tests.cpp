#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "biggest_int.hpp"

TEST(TBiggestIntSuite, outputTest) {
    std::vector<std::string> values{"0", "1", "12", "123", "1234", "12345", "123456", "1234567", "123456789"};

    for (const std::string & expected : values) {
        NBiggestInt::TBigInt_10e6 num(expected);
        const std::string res = num.GetString();
        ASSERT_EQ(expected, res) << "«" << res << "»" << " != " << "«" << expected << "»" << std::endl;
    }
}

TEST(TBiggestIntSuite, leadingZerosTest) {
   std::vector<std::string> values{"0", "01", "0012", "0000123", "001234", "0000012345", "000123456", "00001234567", "0123456789"};
   std::vector<std::string> expectedValues{"0", "1", "12", "123", "1234", "12345", "123456", "1234567", "123456789"};

    for (const std::string & expected : expectedValues) {
        NBiggestInt::TBigInt_10e6 num(expected);
        const std::string res = num.GetString();
        ASSERT_EQ(expected, res) << "«" << res << "»" << " != " << "«" << expected << "»" << std::endl;
    } 
}

TEST(TBiggestIntSuite, sumTest) {
    std::vector<std::string> lhs{"0", "0", "101", "101", "1001009"};
    std::vector<std::string> rhs{"0", "1", "010", "019", "1000001"};
    std::vector<std::string> exp{"0", "1", "111", "120", "2001010"};

    for (size_t i = 0; i < lhs.size(); ++i) {
        NBiggestInt::TBigInt_10e6 num1(lhs[i]);
        NBiggestInt::TBigInt_10e6 num2(rhs[i]);
        NBiggestInt::TBigInt_10e6 expected(exp[i]);
        ASSERT_EQ(expected, num1 + num2) << num1 << " + " << num2 << "!=" << expected;
    }
}

TEST(TBiggestIntSuite, subtractionTest) {
    // Exception test
    {
        NBiggestInt::TBigInt_10e6 num1("123");
        NBiggestInt::TBigInt_10e6 num2("12345678");
        ASSERT_THROW(num1 - num2, std::logic_error);
    }

    // Value test
    {
        std::vector<std::string> lhs{"0", "1", "101", "101", "12345"};
        std::vector<std::string> rhs{"0", "0", "010", "019", "123"};
        std::vector<std::string> exp{"0", "1", "91",  "82",  "12222"};

        for (size_t i = 0; i < lhs.size(); ++i) {
            NBiggestInt::TBigInt_10e6 num1(lhs[i]);
            NBiggestInt::TBigInt_10e6 num2(rhs[i]);
            NBiggestInt::TBigInt_10e6 expected(exp[i]);
            ASSERT_EQ(expected, num1 - num2) << num1 << " - " << num2 << "!=" << expected;
        }
    }
}

TEST(TBiggestIntSuite, multiplicationTest) {
    std::vector<std::string> lhs{"0", "1", "101",  "101",  "123456789123"};
    std::vector<std::string> rhs{"0", "0", "010",  "019",  "123456"};
    std::vector<std::string> exp{"0", "0", "1010", "1919", "15241481357969088"};

    for (size_t i = 0; i < lhs.size(); ++i) {
        NBiggestInt::TBigInt_10e6 num1(lhs[i]);
        NBiggestInt::TBigInt_10e6 num2(rhs[i]);
        NBiggestInt::TBigInt_10e6 expected(exp[i]);
        ASSERT_EQ(expected, num1 * num2) << num1 << " * " << num2 << "!=" << expected;
    }
}

TEST(TBiggestIntSuite, divisionTest) {
    // Exception test
    {
        NBiggestInt::TBigInt_10e6 num1("0");
        NBiggestInt::TBigInt_10e6 num2("0");
        ASSERT_THROW(num1 / num2, std::logic_error);
    }
    
    // Value tests
    {
        std::vector<std::string> lhs{"1", "10", "1231",    "13156819"};
        std::vector<std::string> rhs{"1", "10", "145312",  "145140"};
        std::vector<std::string> exp{"1", "1",  "0",       "90"};

        for (size_t i = 0; i < lhs.size(); ++i) {
            NBiggestInt::TBigInt_10e6 num1(lhs[i]);
            NBiggestInt::TBigInt_10e6 num2(rhs[i]);
            NBiggestInt::TBigInt_10e6 expected(exp[i]);
            ASSERT_EQ(expected, num1 / num2) << num1 << " / " << num2 << "!=" << expected;
        }
    }
}

TEST(TBiggestIntSuite, powTest) {
    // Exception test
    {
        NBiggestInt::TBigInt_10e6 num1("0");
        NBiggestInt::TBigInt_10e6 num2("0");
        ASSERT_THROW(num1.Pow(num2), std::logic_error);
    }
    
    // Value tests
    {
        std::vector<std::string> lhs{"1", "10",  "2",  "123"};
        std::vector<std::string> rhs{"1", "2",  "5",   "13"};
        std::vector<std::string> exp{"1", "100", "32", "1474913153392179474539944683"};

        for (size_t i = 0; i < lhs.size(); ++i) {
            NBiggestInt::TBigInt_10e6 num1(lhs[i]);
            NBiggestInt::TBigInt_10e6 num2(rhs[i]);
            NBiggestInt::TBigInt_10e6 expected(exp[i]);
            ASSERT_EQ(expected, num1.Pow(num2)) << num1 << " ^ " << num2 << "!=" << expected;
        }
    }
}

TEST(TBiggestIntSuite, shiftTest) {
    std::vector<std::string> lhs{"0", "1",       "12"};
    std::vector<long long>   rhs{100,  1,         2};
    std::vector<std::string> exp{"0", "1000000", "12000000000000"};

    for (size_t i = 0; i < lhs.size(); ++i) {
        NBiggestInt::TBigInt_10e6 num1(lhs[i]);
        long long num2 = rhs[i];
        NBiggestInt::TBigInt_10e6 expected(exp[i]);
        
        num1.Shift(num2);
        ASSERT_EQ(expected, num1) << num1 << " << " << num2 << "!=" << expected;
    }
}

TEST(TBiggestIntSuite, karatsubaMultiplicationTest) {
    std::vector<std::string> lhs{"1", "101",  "101",  "123456789123"};
    std::vector<std::string> rhs{"0", "010",  "019",  "123456"};
    std::vector<std::string> exp{"0", "1010", "1919", "15241481357969088"};

    for (size_t i = 0; i < lhs.size(); ++i) {
        NBiggestInt::TBigInt_10e6 num1(lhs[i]);
        NBiggestInt::TBigInt_10e6 num2(rhs[i]);
        NBiggestInt::TBigInt_10e6 expected(exp[i]);
        ASSERT_EQ(expected, NBiggestInt::TBigInt_10e6::KaratsubaMultiplication(std::move(num1), std::move(num2))) << num1 << " * " << num2 << "!=" << expected;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}