#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

namespace BigInt_e6 {

class TBigInt_e6 {
    public:
        static const int BASE = 1e6; 
        static const int RADIX = 6;

        TBigInt_e6() = default;
        TBigInt_e6(const std::string & str);
        TBigInt_e6(const size_t & length, const long long value = 0);
        void Initialize(const std::string & str);
        std::string GetStr() const;

        size_t Size() const;
        TBigInt_e6 Power(const TBigInt_e6 & degree) const;
        void Shift(const long long degree);
        static TBigInt_e6 KaratsubaMult(TBigInt_e6 && lhs, TBigInt_e6 && rhs);

        TBigInt_e6 & operator=(const TBigInt_e6 & rhs);

        TBigInt_e6 operator+(const TBigInt_e6 & rhs) const;
        TBigInt_e6 operator-(const TBigInt_e6 & rhs) const;
        TBigInt_e6 operator*(const TBigInt_e6 & rhs) const;
        TBigInt_e6 operator/(const TBigInt_e6 & rhs) const;

        TBigInt_e6 operator-(const long long rhs) const;
        TBigInt_e6 operator*(const long long rhs) const;
        TBigInt_e6 operator/(const long long rhs) const;
        long long   operator%(const long long rhs) const;

        bool operator< (const TBigInt_e6 & rhs) const;
        bool operator<=(const TBigInt_e6 & rhs) const;
        bool operator> (const TBigInt_e6 & rhs) const;
        bool operator==(const TBigInt_e6 & rhs) const;
        bool operator==(const long long     rhs) const;
        bool operator> (const long long     rhs) const;

        friend std::istream& operator>>(std::istream &is, TBigInt_e6 & rhs);
        friend std::ostream& operator<<(std::ostream &os, const TBigInt_e6 & rhs);
    private:
        std::vector<long long> digits;

        void DeleteLeadingZeros();
};

} // namespace NBiggestInt
