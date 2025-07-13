#include "Integer.hpp"
#include <stdexcept>
#include <tuple>


static std::tuple<Integer, Integer, Integer> extended_gcd(const Integer& a, const Integer& b) {
    Integer old_r = a, r = b;
    Integer old_s = Integer(1), s = Integer(0);
    Integer old_t = Integer(0), t = Integer(1);

    while (r != Integer(0)) {
        Integer quotient = old_r / r;

        Integer temp = r;
        r = old_r - quotient * r;
        old_r = temp;

        temp = s;
        s = old_s - quotient * s;
        old_s = temp;

        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }

    return {old_r, old_s, old_t};
}

// Returns x such that (a * x) % m == 1
Integer mod_inverse(const Integer& a, const Integer& m) {
    if (m == Integer(0))
        throw std::invalid_argument("Modulus must be non-zero");
    if (m < Integer(0))
        throw std::invalid_argument("Modulus must be greater than zero");
    if (a == Integer(0))
        throw std::invalid_argument("Inverse does not exist for zero");

    Integer mod = m.abs();
    Integer base = a % mod;

    auto [g, x, y] = extended_gcd(base, mod);
    if (g != Integer(1))
        throw std::invalid_argument("Inverse does not exist for these values");

    x %= mod;
    if (x < Integer(0))
        x += mod;
    return x;
}

// Member wrapper that calls the free function above
Integer Integer::mod_inverse(const Integer& a, const Integer& m) {
    return ::mod_inverse(a, m);
}


// Computes Integral Exponentiation Using Successive Squaring
Integer Integer::power(const Integer& exponent) const {
    if (exponent.isNegative)
        throw std::invalid_argument("Negative exponent not supported");

    Integer result(1);
    Integer base = *this;
    Integer exp = exponent;

    while (exp != Integer(0)) {
        if (exp.getBit(0))
            result *= base;
        base *= base;
        exp >>= 1;
    }

    return result;
}

// Computes
Integer Integer::power_mod(const Integer& exponent, const Integer& modulus) const {
    if (exponent.isNegative)
        throw std::invalid_argument("Negative exponent not supported");
    if (modulus == Integer(0))
        throw std::invalid_argument("Modulus must be non-zero");

    Integer result(1);
    Integer base = *this % modulus;
    Integer exp = exponent;

    while (exp != Integer(0)) {
        if (exp.getBit(0))
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }

    return result;
}
