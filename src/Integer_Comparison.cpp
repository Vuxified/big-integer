#include "Integer.hpp"

// Equality
bool Integer::operator==(const Integer& rhs) const {
    return isNegative == rhs.isNegative && limbs == rhs.limbs;
}

bool Integer::operator!=(const Integer& rhs) const {
    return !(*this == rhs);
}

// Less than
// bool Integer::operator<(const Integer& rhs) const {
//     if (isNegative != rhs.isNegative) {
//         return isNegative && !(limbs.size() == 1 && limbs[0] == 0 &&
//                                rhs.limbs.size() == 1 && rhs.limbs[0] == 0);
//     }

//     if (limbs.size() != rhs.limbs.size()) {
//         if (isNegative)
//             return limbs.size() > rhs.limbs.size();
//         else
//             return limbs.size() < rhs.limbs.size();
//     }

//     for (size_t i = limbs.size(); i-- > 0;) {
//         if (limbs[i] != rhs.limbs[i]) {
//             if (isNegative)
//                 return limbs[i] > rhs.limbs[i];
//             else
//                 return limbs[i] < rhs.limbs[i];
//         }
//     }
//     return false;
// }

bool Integer::operator<(const Integer& rhs) const {
    if (isNegative != rhs.isNegative) {
        return isNegative && !(limbs.size() == 1 && limbs[0] == 0 &&
            rhs.limbs.size() == 1 && rhs.limbs[0] == 0);
    }
   if (limbs.size() != rhs.limbs.size()) {
      if (isNegative)
            return limbs.size() > rhs.limbs.size();
        else
            return limbs.size() < rhs.limbs.size();
    }
      for (size_t i = limbs.size(); i-- > 0;) {
          if (limbs[i] != rhs.limbs[i]) {
              if (isNegative)
                  return limbs[i] > rhs.limbs[i];
              else
                  return limbs[i] < rhs.limbs[i];
          }
      }
      return false;
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
