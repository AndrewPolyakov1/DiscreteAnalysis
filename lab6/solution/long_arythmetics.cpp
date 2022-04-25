#include "long_arythmetics.hpp"
#include <algorithm>
#include <sstream>

namespace BigInt_e6 {

TBigInt_e6::TBigInt_e6(const std::string & str) {
    this->Initialize(str);
}

TBigInt_e6::TBigInt_e6(const size_t & length, const long long value) 
    : digits(length, value)
{}

void TBigInt_e6::Initialize(const std::string & str) {
    long long startIdx = 0;
    while (startIdx < str.size() && str[startIdx] == '0') {
        ++startIdx;
    }
    if (startIdx == str.size()) {
        digits.push_back(0);
        return;
    }

    digits.clear();
    size_t digitsSize = (str.size() - startIdx) / RADIX;
    if ((str.size() - startIdx) % RADIX != 0) {
        ++digitsSize;
    }
    digits.resize(digitsSize);

    size_t digitsCount = 0;
    for (long long i = str.size() - 1; i >= startIdx; i -= RADIX) {
        long long currDigit = 0;
        long long digitStart = i - RADIX + 1;
        if (digitStart < 0 || digitStart <= startIdx) {
            digitStart = 0;
        }
        for (long long j = digitStart; j <= i; ++j) {
            currDigit = currDigit * 10 + str[j] - '0';
        }

        digits[digitsCount] = currDigit;
        ++digitsCount;
    }
}

size_t TBigInt_e6::Size() const {
    return digits.size();
}

TBigInt_e6& TBigInt_e6::operator=(const TBigInt_e6 & rhs) {
    digits.resize(rhs.Size());
    for (size_t i = 0; i < Size(); ++i) {
        digits[i] = rhs.digits[i];
    }
    return *this;
}

void TBigInt_e6::DeleteLeadingZeros() {
    while (Size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

// Streams operators

std::istream& operator>>(std::istream & is, TBigInt_e6 & rhs) {
    std::string str;
    is >> str;
    rhs.Initialize(str);
    return is;
}

std::ostream& operator<<(std::ostream & os, const TBigInt_e6 & rhs) {
    os << rhs.digits[rhs.Size()- 1];
    for (long long i = rhs.Size() - 2; i >= 0; --i) {
        os << std::setfill('0') << std::setw(TBigInt_e6::RADIX) << rhs.digits[i]; 
    }
    return os;
}

std::string TBigInt_e6::GetStr() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// Operators for TBiggestInt

TBigInt_e6 TBigInt_e6::operator+(const TBigInt_e6 & rhs) const {
    size_t resSize = std::max(rhs.Size(), Size());
    TBigInt_e6 res(resSize);
    long long carry = 0;

    for (size_t i = 0; i < resSize; ++i) {
        long long sum = carry;
        if (i < rhs.Size()) {
            sum += rhs.digits[i];
        }
        if (i < Size()) {
            sum += digits[i];
        }
        carry = sum / BASE;
        res.digits[i] = sum % BASE;
    }
    if (carry != 0) {
        res.digits.push_back(carry);
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt_e6 TBigInt_e6::operator-(const TBigInt_e6 & rhs) const {
    if (*this < rhs) {
        throw std::logic_error("Error: trying to subtract bigger number from smaller");
    }

    size_t resSize = std::max(rhs.Size(), Size());
    long long carry = 0;
    TBigInt_e6 res(resSize);

    for (size_t i = 0; i < resSize; ++i) {
        long long diff = digits[i] - carry;
        if (i < rhs.Size()) {
            diff -= rhs.digits[i];
        }

        if (diff < 0) {
            carry = 1;
            diff += BASE;
        } else {
            carry = 0;
        }
        res.digits[i] = diff % BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt_e6 TBigInt_e6::operator*(const TBigInt_e6 & rhs) const {
    TBigInt_e6 res(Size() + rhs.Size());
    for (size_t i = 0; i < Size(); ++i) {
        long long carry = 0;
        for (size_t j = 0; j < rhs.Size() || carry > 0; ++j) {
            long long current = res.digits[i + j] + carry;
            if (j < rhs.Size()) {
                current += digits[i] * rhs.digits[j];
            }
            res.digits[i + j] = current % BASE;
            carry = current / BASE;
        }
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt_e6 TBigInt_e6::operator/(const TBigInt_e6 & rhs) const {
    if (rhs == 0) {
        throw std::logic_error("Error: Trying to divide by zer0");
    }

    TBigInt_e6 res;
    TBigInt_e6 curr;
    for (size_t i = Size() - 1; i < Size(); --i) {
        curr.digits.insert(std::begin(curr.digits), digits[i]);
        curr.DeleteLeadingZeros();

        long long currResDigit = 0;
        long long leftBound = 0;
        long long rightBound = BASE;
        while (leftBound <= rightBound) {
            long long middle = (leftBound + rightBound) / 2;
            TBigInt_e6 tmp = rhs * middle;
            if (tmp <= curr) {
                currResDigit = middle;
                leftBound = middle + 1;
            }
            else {
                rightBound = middle - 1;
            }   
        }

        res.digits.insert(std::begin(res.digits), currResDigit);
        curr = curr - rhs * currResDigit;
    }

    res.DeleteLeadingZeros();
    return res;

}

void TBigInt_e6::Shift(const long long degree) {
    if (*this == 0) {
        return;
    }

    size_t oldSize = digits.size();
    digits.resize(digits.size() + degree);

    for (long long i = oldSize - 1; i >= 0; --i) {
        digits[i + degree] = digits[i];
    }
    for (long long i = 0; i < degree; ++i) {
        digits[i] = 0;
    }
}

TBigInt_e6 TBigInt_e6::KaratsubaMult(TBigInt_e6 && lhs, TBigInt_e6 && rhs) {
    size_t length = std::max(lhs.Size(), rhs.Size());
    if (length == 1) {
        return lhs * rhs.digits.back();
    }

    if (length % 2 != 0) {
        ++length;
    }

    lhs.digits.resize(length);
    rhs.digits.resize(length);

    TBigInt_e6 leftHalfLhs;
    TBigInt_e6 rightHalfLhs;
    std::copy(std::begin(lhs.digits), std::begin(lhs.digits) + (length / 2), std::back_inserter(rightHalfLhs.digits));
    std::copy(std::begin(lhs.digits) + (length / 2), std::end(lhs.digits) , std::back_inserter(leftHalfLhs.digits));

    TBigInt_e6 leftHalfRhs;
    TBigInt_e6 rightHalfRhs;
    std::copy(std::begin(rhs.digits), std::begin(rhs.digits) + (length / 2), std::back_inserter(rightHalfRhs.digits));
    std::copy(std::begin(rhs.digits) + (length / 2), std::end(rhs.digits) , std::back_inserter(leftHalfRhs.digits));

    // res = BASE^n * Prod1 + BASE^(n/2)*(Prod2 - Prod1 - Prod3) + Prod 3
    TBigInt_e6 Term1 = KaratsubaMult(std::move(leftHalfLhs), std::move(leftHalfRhs));
    TBigInt_e6 Term2 = KaratsubaMult(leftHalfLhs + rightHalfLhs, leftHalfRhs + rightHalfRhs);
    TBigInt_e6 Term3 = KaratsubaMult(std::move(rightHalfLhs), std::move(rightHalfRhs));
    
    Term2 = Term2 - Term1 - Term3;
    Term1.Shift(length);
    Term2.Shift(length / 2);
    
    TBigInt_e6 result = Term1 + Term2 + Term3;

    unsigned long long carry = 0;
    for (unsigned long long i = 0; i < result.Size(); ++i) {
        result.digits[i] += carry;
        carry = result.digits[i] / BASE;
        result.digits[i] %= BASE;
    }

    if (carry != 0) {
        result.digits.push_back(carry);
    }

    return result;
}

TBigInt_e6 TBigInt_e6::Power(const TBigInt_e6 & degree) const {
    if (*this == 0 && degree == 0) {
        throw std::logic_error("Error: 0^0 is uncertain");
    }

    TBigInt_e6 res("1");
    if (degree == 0) {
        return res;
    }

    TBigInt_e6 curr = *this;
    TBigInt_e6 currDegree = degree;
    while (currDegree > 0) {
        if (currDegree.digits.back() % 2 != 0) {
            res = res * curr;
        }

        curr = curr * curr;
        currDegree = currDegree / 2;
    }
    return res;
}

// Operators for long longs

TBigInt_e6 TBigInt_e6::operator-(const long long rhs) const {
    if (Size() == 1 && digits[0] < rhs) {
        throw std::logic_error("Error: trying to subtract bigger number from smaller");
    }

    TBigInt_e6 res = *this;
    int idx = 0;
    res.digits[0] -= rhs;
    while (res.digits[idx] < 0) {
        --res.digits[idx + 1];
        res.digits[idx++] += BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt_e6 TBigInt_e6::operator*(const long long rhs) const {
    TBigInt_e6 res(Size());
    long long carry = 0;
    for (size_t i = 0; i < Size() || carry > 0; ++i) {
        long long currDigit = carry;
        if (i == Size()) {
            res.digits.push_back(0);
        } else {
            currDigit += digits[i] * rhs;
        }
        res.digits[i] = currDigit % BASE;
        carry = currDigit / BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBigInt_e6 TBigInt_e6::operator/(const long long rhs) const {
    TBigInt_e6 res(Size());
    long long carry = 0;
    for (size_t i = Size() - 1; i < Size(); --i) {
        long long currDigit = carry * BASE + digits[i];
        res.digits[i] = currDigit / rhs;
        carry = currDigit % rhs;
    }
    res.DeleteLeadingZeros();
    return res;
}

long long TBigInt_e6::operator%(const long long rhs) const {
    long long carry = 0;
    for (size_t i = Size() - 1; i < Size(); --i) {
        carry = ( carry * BASE + digits[i] ) % rhs;
    }
    return carry;
}

// Comparasion operators

bool TBigInt_e6::operator< (const TBigInt_e6 & rhs) const {
    if (Size() != rhs.Size()) {
        return Size() < rhs.Size();
    }

    for (size_t i = Size() - 1; i < Size(); --i) { 
        if (digits[i] != rhs.digits[i]) {
            return digits[i] < rhs.digits[i];
        }
    }

    return false; 
}

bool TBigInt_e6::operator<= (const TBigInt_e6 & rhs) const {
    return !(*this > rhs);
}

bool TBigInt_e6::operator> (const TBigInt_e6 & rhs) const {
    if (Size() != rhs.Size()) {
        return Size() > rhs.Size();
    }

    for (size_t i = Size() - 1; i < Size(); --i) { 
        if (digits[i] != rhs.digits[i]) {
            return digits[i] > rhs.digits[i];
        }
    }

    return false; 
}

bool TBigInt_e6::operator==(const TBigInt_e6 & rhs) const {
    if (Size() != rhs.Size()) {
        return false;
    }

    for (size_t i = Size() - 1; i < Size(); --i) { 
        if (digits[i] != rhs.digits[i]) {
            return false;
        }
    }

    return true;
}

bool TBigInt_e6::operator==(const long long rhs) const {
    if (Size() != 1) {
        return false;
    }
    return digits.back() == rhs;
}

bool TBigInt_e6::operator> (const long long rhs) const {
    if (Size() > 1) {
        return true;
    }
    return digits.back() > rhs;
}

} // namespace NBiggestInt