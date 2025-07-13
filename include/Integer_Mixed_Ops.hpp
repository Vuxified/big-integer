// Some parts of this file are missing and you need to complete it.

#ifndef INTEGER_MIXED_OPS_HPP
#define INTEGER_MIXED_OPS_HPP

#include "Integer.hpp"
#include <type_traits>

Integer mod_inverse(const Integer& a, const Integer& m);


// Arithmetic: T op Integer
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
inline Integer operator+(T lhs, const Integer& rhs) { return Integer(lhs) + rhs;}


// Bitwise: T op Integer
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
inline Integer operator&(T lhs, const Integer& rhs) {return Integer(lhs) & rhs;}



// Bitwise: Integer op T
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
inline Integer operator&(const Integer& lhs, T rhs) {return lhs & Integer(rhs);}



// Comparison: T op Integer


// Comparison: Integer op T


// Modular Arithmetic: 


/*

***********  I RECOMMEND NOT CHANGING ANYTHING BELOW THIS LINE **********************

*/


// To avoid ambiguous situations -- Apply template if neither argument is already an Integer
template <typename T1, typename T2,
          typename = std::enable_if_t<
              std::is_integral_v<T1> &&
              std::is_integral_v<T2> &&
              !std::is_same_v<T1, Integer> &&
              !std::is_same_v<T2, Integer>
          >>
inline Integer mod_inverse(T1 a, T2 m) {return mod_inverse(Integer(a), Integer(m));  }


template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
inline Integer power(const Integer& base, T exponent) {return base.power(Integer(exponent));}

template <typename T1, typename T2, typename T3,
          typename = std::enable_if_t<std::is_integral_v<T1> &&
                                      std::is_integral_v<T2> &&
                                      std::is_integral_v<T3>>>
inline Integer power_mod(T1 base, T2 exponent, T3 modulus) {
    return Integer(base).power_mod(Integer(exponent), Integer(modulus));
}

template <typename T1, typename T2,
          typename = std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>>>
inline Integer power_mod(const Integer& base, T1 exponent, T2 modulus) {
    return base.power_mod(Integer(exponent), Integer(modulus));
}


#endif // INTEGER_MIXED_OPS_HPP
