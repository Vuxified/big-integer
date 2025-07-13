

#include "Integer.hpp"
#include <ostream>


void Integer::normalize() {

}


std::string Integer::toString() const {

}

Integer Integer::abs() const {

}

// Returns the greatest common divisor of a and b
Integer Integer::gcd(const Integer& a, const Integer& b) {

}

Integer Integer::lcm(const Integer& a, const Integer& b)  {

}


// Below is just fine.  Just implement toString correctly to make it work.
std::ostream& operator<<(std::ostream& os, const Integer& val) {
    return os << val.toString();
}