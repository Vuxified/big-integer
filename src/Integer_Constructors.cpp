#include "Integer.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

Integer::Integer() {
    limbs.push_back(0);
}

Integer::Integer(int64_t n) {
    isNegative = (n < 0);
    uint64_t absval = isNegative ? -n : n;
    do {
        limbs.push_back(absval % LIMB_BASE);
        absval /= LIMB_BASE;
    } while (absval > 0);
}

Integer::Integer(const std::string& str) {
    if (str.empty())
        throw std::invalid_argument("Empty string");

    size_t pos = 0;
    if (str[pos] == '-') {
        isNegative = true;
        ++pos;
    } else if (str[pos] == '+') {
        ++pos;
    }

    while (pos < str.size() && str[pos] == '0')
        ++pos;

    if (pos == str.size()) {
        limbs.push_back(0);
        isNegative = false;
        return;
    }

    limbs.push_back(0);
    for (; pos < str.size(); ++pos) {
        if (!std::isdigit(static_cast<unsigned char>(str[pos])))
            throw std::invalid_argument("Invalid digit in string");

        uint32_t digit = static_cast<uint32_t>(str[pos] - '0');
        uint64_t carry = digit;
        for (size_t i = 0; i < limbs.size(); ++i) {
            uint64_t val = static_cast<uint64_t>(limbs[i]) * 10 + carry;
            limbs[i] = static_cast<Limb>(val % LIMB_BASE);
            carry = val / LIMB_BASE;
        }
        if (carry)
            limbs.push_back(static_cast<Limb>(carry));
    }

    normalize();
}