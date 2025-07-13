#include "Integer.hpp"
#include <algorithm>
#include <stdexcept>

// Bitwise AND (Just fine the way it is)
Integer Integer::operator&(const Integer& rhs) const {
    Integer result;
    size_t n = std::min(limbs.size(), rhs.limbs.size());
    result.limbs.resize(n);
    for (size_t i = 0; i < n; ++i)
        result.limbs[i] = limbs[i] & rhs.limbs[i];
    result.normalize();
    return result;
}

// Bitwise OR
Integer Integer::operator|(const Integer& rhs) const {

}

// Bitwise XOR
Integer Integer::operator^(const Integer& rhs) const {

}

// Bitwise NOT (only defined for non-negative values)
Integer Integer::operator~() const {

}

// Left shift


// Right shift (Just fine the way it is)
Integer Integer::operator>>(int shift) const {
    Integer result = *this;
    result >>= shift;
    return result;
}

// Just fine the way it is
Integer& Integer::operator>>=(int shift) {
    if (shift < 0) return *this <<= -shift;
    int limb_shift = shift / 32;
    int bit_shift = shift % 32;

    if (limb_shift >= static_cast<int>(limbs.size())) {
        limbs = {0};
        isNegative = false;
        return *this;
    }

    limbs.erase(limbs.begin(), limbs.begin() + limb_shift);
    if (bit_shift == 0) {
        normalize();
        return *this;
    }

    uint64_t carry = 0;
    for (int i = static_cast<int>(limbs.size()) - 1; i >= 0; --i) {
        uint64_t val = (static_cast<uint64_t>(limbs[i]) | (carry << 32)) >> bit_shift;
        carry = limbs[i] & ((1ULL << bit_shift) - 1);
        limbs[i] = static_cast<Limb>(val);
    }
    normalize();
    return *this;
}

void Integer::setBit(int i) {

}

bool Integer::getBit(int i) const {

}
