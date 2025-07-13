#include "Integer.hpp"

// Equality
bool Integer::operator==(const Integer& rhs) const {
    return isNegative == rhs.isNegative && limbs == rhs.limbs;
}

bool Integer::operator!=(const Integer& rhs) const {
    return !(*this == rhs);
}

// Less than
bool Integer::operator<(const Integer& rhs) const {

}

// Less than or equal
bool Integer::operator<=(const Integer& rhs) const {
    return *this < rhs || *this == rhs;
}

// Greater than
bool Integer::operator>(const Integer& rhs) const {
    return !(*this <= rhs);
}

// Greater than or equal
bool Integer::operator>=(const Integer& rhs) const {
    return !(*this < rhs);
}
