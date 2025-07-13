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

}

