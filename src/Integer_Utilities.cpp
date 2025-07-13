#include "Integer.hpp"
#include <ostream>
#include <algorithm>


// Removes angity leading zero limbs and ensures the sign is
// positive when the value is zero.
void Integer::normalize() {

    // Erase limbs from the back while there are more than
    // one limb and the most significant limb is zero.
    while (limbs.size() > 1 && limbs.back() == 0) {
        limbs.pop_back();
    }
    // If the number has become zero, clear the negative flag
    if (limbs.size() == 1 && limbs[0] == 0) {
        isNegative = false;
    }
}


// Converts the internal base 2^32 representation to a base 10 string.
std::string Integer::toString() const {

    // Handle zero explicitly
    if (limbs.size() == 1 && limbs[0] == 0) {
        return "0";
    }

    // Make a copy of the absolute value to perform divisions on
    std::vector<Limb> temp = limbs;
    bool negative = isNegative;

    auto divide_by = [](std::vector<Limb>& number, uint32_t divisor) -> uint32_t {
        uint64_t remainder = 0;
        // Process limbs from most significant to least significant
        for (int i = static_cast<int>(number.size()) - 1; i >= 0; --i) {
            uint64_t cur = (remainder << 32) | number[i];
            number[i] = static_cast<Limb>(cur / divisor);
            remainder = cur % divisor;
        }
        // Remove any new leading zeros
        while (number.size() > 1 && number.back() == 0) {
            number.pop_back();
        }
        return static_cast<uint32_t>(remainder);
    };

    std::string digits;
    // Repeatedly divide the number by 10 to extract decimal digits
    while (!(temp.size() == 1 && temp[0] == 0)) {
        uint32_t rem = divide_by(temp, 10);
        digits.push_back(static_cast<char>('0' + rem));
    }

    if (negative) {
        digits.push_back('-');
    }
    // Digits were collected in reverse order
    std::reverse(digits.begin(), digits.end());
    return digits;
}

// Returns a non-negative copy of this Integer.
Integer Integer::abs() const {

    Integer result = *this;
    result.isNegative = false;
    return result;
}

// Returns the greatest common divisor using the Euclidean algorithm.
Integer Integer::gcd(const Integer& a, const Integer& b) {

    Integer x = a.abs();
    Integer y = b.abs();
    while (!(y == Integer(0))) {
        Integer r = x % y;
        x = y;
        y = r;
    }
    return x;
}

// Returns the least common multiple of a and b.
Integer Integer::lcm(const Integer& a, const Integer& b)  {

    if (a == Integer(0) || b == Integer(0)) {
        return Integer(0);
    }
    Integer g = Integer::gcd(a, b);
    return (a / g).abs() * b.abs();
}


// Below is just fine.  Just implement toString correctly to make it work.
std::ostream& operator<<(std::ostream& os, const Integer& val) {
    return os << val.toString();
}
