#include "Integer.hpp"
#include <algorithm>
#include <stdexcept>

// Helper to compare absolute values. Returns -1,0,1 for <,==,>
static int absCompare(const Integer& a, const Integer& b) {
    if (a.limbs.size() != b.limbs.size())
        return (a.limbs.size() < b.limbs.size()) ? -1 : 1;
    for (size_t i = a.limbs.size(); i-- > 0;) {
        if (a.limbs[i] != b.limbs[i])
            return (a.limbs[i] < b.limbs[i]) ? -1 : 1;
    }
    return 0;
}

// Addition assignment
Integer& Integer::operator+=(const Integer& rhs) {
    if (rhs == Integer(0)) {
        return *this;
    }

    if (isNegative == rhs.isNegative) {
        size_t n = std::max(limbs.size(), rhs.limbs.size());
        limbs.resize(n, 0);
        uint64_t carry = 0;
        for (size_t i = 0; i < n; ++i) {
            uint64_t a = limbs[i];
            uint64_t b = (i < rhs.limbs.size()) ? rhs.limbs[i] : 0;
            uint64_t sum = a + b + carry;
            limbs[i] = static_cast<Limb>(sum & 0xFFFFFFFFu);
            carry = sum >> 32;
        }
        if (carry)
            limbs.push_back(static_cast<Limb>(carry));
    } else {
        // different signs -> perform subtraction of absolute values
        if (absCompare(*this, rhs) >= 0) {
            uint64_t borrow = 0;
            for (size_t i = 0; i < limbs.size(); ++i) {
                uint64_t a = limbs[i];
                uint64_t b = (i < rhs.limbs.size()) ? rhs.limbs[i] : 0;
                uint64_t val = a - b - borrow;
                if (a < b + borrow) {
                    val += LIMB_BASE;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                limbs[i] = static_cast<Limb>(val);
            }
        } else {
            std::vector<Limb> result(rhs.limbs);
            uint64_t borrow = 0;
            for (size_t i = 0; i < result.size(); ++i) {
                uint64_t a = result[i];
                uint64_t b = (i < limbs.size()) ? limbs[i] : 0;
                uint64_t val = a - b - borrow;
                if (a < b + borrow) {
                    val += LIMB_BASE;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result[i] = static_cast<Limb>(val);
            }
            limbs.swap(result);
            isNegative = rhs.isNegative;
        }
    }
    normalize();
    return *this;
}

// Subtraction assignment implemented using addition of the negated value
Integer& Integer::operator-=(const Integer& rhs) {
    *this += (-rhs);
    return *this;
}

// Multiplication assignment using schoolbook multiplication
Integer& Integer::operator*=(const Integer& rhs) {
    if (*this == Integer(0) || rhs == Integer(0)) {
        limbs.assign(1, 0);
        isNegative = false;
        return *this;
    }

    std::vector<Limb> result(limbs.size() + rhs.limbs.size(), 0);
    for (size_t i = 0; i < limbs.size(); ++i) {
        uint64_t carry = 0;
        for (size_t j = 0; j < rhs.limbs.size(); ++j) {
            uint64_t cur = static_cast<uint64_t>(limbs[i]) * rhs.limbs[j] + result[i + j] + carry;
            result[i + j] = static_cast<Limb>(cur & 0xFFFFFFFFu);
            carry = cur >> 32;
        }
        result[i + rhs.limbs.size()] += static_cast<Limb>(carry);
    }

    limbs.swap(result);
    isNegative = (isNegative != rhs.isNegative);
    normalize();
    return *this;
}

// Division assignment (naive long division)
Integer& Integer::operator/=(const Integer& rhs) {
    if (rhs == Integer(0))
        throw std::invalid_argument("Division by zero");

    bool neg = isNegative != rhs.isNegative;
    Integer dividend = this->abs();
    Integer divisor = rhs.abs();

    if (absCompare(dividend, divisor) < 0) {
        limbs.assign(1, 0);
        isNegative = false;
        return *this;
    }

    std::vector<Limb> q(dividend.limbs.size(), 0);
    Integer remainder;
    for (int i = static_cast<int>(dividend.limbs.size()) - 1; i >= 0; --i) {
        remainder.limbs.insert(remainder.limbs.begin(), dividend.limbs[i]);
        remainder.normalize();

        uint32_t low = 0, high = 0xFFFFFFFFu, best = 0;
        while (low <= high) {
            uint32_t mid = low + ((high - low) >> 1);
            Integer prod = divisor;
            prod *= Integer(mid);
            if (absCompare(prod, remainder) <= 0) {
                best = mid;
                low = mid + 1;
            } else {
                if (mid == 0) break;
                high = mid - 1;
            }
        }

        q[i] = best;
        if (best != 0) {
            Integer prod = divisor;
            prod *= Integer(best);
            remainder -= prod;
        }
    }

    limbs = q;
    isNegative = neg && !(q.size() == 1 && q[0] == 0);
    normalize();
    return *this;
}

// Modulo assignment using quotient multiplication
Integer& Integer::operator%=(const Integer& rhs) {
    if (rhs == Integer(0))
        throw std::invalid_argument("Division by zero");
    Integer quotient = *this / rhs;
    *this -= quotient * rhs;
    return *this;
}





// YOU MAY FIND IT EASIER TO IMPLEMENT += and then use that for +.

// Binary operators

//This operation is fine the way it is.
Integer Integer::operator+(const Integer& rhs) const {
    Integer result = *this;
    result += rhs;
    return result;
}





// Pre-increment (++x) (Just fine)
Integer& Integer::operator++() {
    *this += Integer(1);
    return *this;
}

// Post-increment (x++)  (Just fine)
Integer Integer::operator++(int) {
    Integer temp = *this;
    ++(*this);
    return temp;
}


// This operation is just fine the way it is.
Integer Integer::operator-() const {
    Integer result = *this;
    if (result != Integer(0)) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

// Binary subtraction
Integer Integer::operator-(const Integer& rhs) const {
    Integer result = *this;
    result -= rhs;
    return result;
}

// Binary multiplication
Integer Integer::operator*(const Integer& rhs) const {
    Integer result = *this;
    result *= rhs;
    return result;
}

// Binary division
Integer Integer::operator/(const Integer& rhs) const {
    Integer result = *this;
    result /= rhs;
    return result;
}

// Binary modulo
Integer Integer::operator%(const Integer& rhs) const {
    Integer result = *this;
    result %= rhs;
    return result;
}

// Pre-decrement (--x)
Integer& Integer::operator--() {
    *this -= Integer(1);
    return *this;
}

// Post-decrement (x--)
Integer Integer::operator--(int) {
    Integer temp = *this;
    --(*this);
    return temp;
}
