#include "Integer.hpp"
#include <algorithm>
#include <stdexcept>

// Addition assignment
Integer& Integer::operator+=(const Integer& rhs) {
    // The vectors are 32 bit values.  You can use 64 bit intermediate calculations to estimate carry instances
}

// Subtraction assignment
Integer& Integer::operator-=(const Integer& rhs) {
    // The vectors are 32 bit values.  You can use 64 bit intermediate calculations to estimate carry instances
}

// Multiplication assignment
Integer& Integer::operator*=(const Integer& rhs) {
    std::vector<Limb> result(limbs.size() + rhs.limbs.size(), 0);
    // The vectors are 32 bit values.  You can use 64 bit intermediate calculations to estimate carry instances
}

// Division assignment (naive long division)
Integer& Integer::operator/=(const Integer& rhs) {
    if (rhs == Integer(0))
        throw std::invalid_argument("Division by zero");

    // This part does not need to be optimized. 
    // I recommend implementing the bitwise division algorithm for better performance.
    // You should probably build out the other arithmetic operators first.
    // Then you should implement the bitwise operations.
    // You can then use the bitwise operations to implement the division operator.

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