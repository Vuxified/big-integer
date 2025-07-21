Arbitrary-Precision Integers

The goal is to produce a modular `Integer` class whose behavior mirrors arithmetic with primitive language integers (e.g. `int`). 

*  I Implement utility methods:

  * `abs()` – returns the absolute value
  * `normalize()` – ensures internal representation has no leading zeros
  * `setBit(int)`, `getBit(int)` – for accessing/modifying individual bits
  * `gcd(Integer a, Integer b)` - Calculate the GCD of two large integers
  * `lcm(Integer a, Integer b)` - Calculatte the LCM of two large integers
* Implement modular arithmetic:
  * `power()` – exponentiation using successive squaring
  * `power_mod()` – modular exponentiation
  * `mod_inverse()` – multiplicative inverse when `gcd(a, m) = 1`
* Overload the `<<` operator for output (printing strings using `cout`).


