#ifndef INFIZ_RATIONAL_NUMBER_H
#define INFIZ_RATIONAL_NUMBER_H

#include <compare>
#include <cstdlib>
#include <numeric>

/**
 * A Class that stores the numerator and denominator
 * of a rational number.
 */
class RationalNumber
{
public:
  constexpr RationalNumber(int num, int den) noexcept// NOLINT
    : numerator(num), denominator(den)
  {}

  [[nodiscard]] constexpr auto simplify() const noexcept -> RationalNumber
  {
    // Handle negative denominators - move the negative sign to the numerator
    if (denominator < 0) { return RationalNumber(-numerator, -denominator).simplify(); }

    const auto gcd = std::gcd(std::abs(numerator), denominator);
    if (gcd == 0) {
      return *this;
    } else {
      return { numerator / gcd, denominator / gcd };
    }
  }

  [[nodiscard]] constexpr auto operator/(const RationalNumber &rhs) const noexcept
  {
    // Check for division by zero - return 1/0 which will be infinity when displayed as float
    if (rhs.getNumerator() == 0) { return RationalNumber{ 1, 0 }; }
    return RationalNumber{ numerator * rhs.getDenominator(), denominator * rhs.getNumerator() }.simplify();
  }

  [[nodiscard]] constexpr auto operator*(const RationalNumber &rhs) const noexcept
  {
    return RationalNumber{ numerator * rhs.getNumerator(), denominator * rhs.getDenominator() }.simplify();
  }

  [[nodiscard]] constexpr auto operator+(const RationalNumber &rhs) const noexcept
  {
    return RationalNumber{ numerator * rhs.getDenominator() + (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() }
      .simplify();
  }

  [[nodiscard]] constexpr auto operator-(const RationalNumber &rhs) const noexcept
  {
    return RationalNumber{ numerator * rhs.getDenominator() - (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() }
      .simplify();
  }

  [[nodiscard]] constexpr auto getDenominator() const noexcept -> int { return denominator; }

  [[nodiscard]] constexpr auto operator-() const -> RationalNumber { return { numerator * -1, denominator }; }

  [[nodiscard]] constexpr auto getNumerator() const noexcept -> int { return numerator; }


  template<std::floating_point Float> [[nodiscard]] constexpr auto asFloat() const noexcept -> Float
  {
    return ((static_cast<Float>(numerator)) / (static_cast<Float>(denominator)));
  }

  [[nodiscard]] constexpr auto operator<=>(const RationalNumber &rhs) const noexcept = default;

private:
  int numerator;
  int denominator;
};

#endif