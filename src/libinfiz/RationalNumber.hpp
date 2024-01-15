#ifndef INFIZ_RATIONAL_NUMBER_H
#define INFIZ_RATIONAL_NUMBER_H

// RationalNumber.h
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
    const auto gcd = std::gcd(numerator, denominator);
    return {numerator / gcd, denominator / gcd};
  }

  [[nodiscard]] constexpr auto operator/(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return RationalNumber{ numerator * rhs.getDenominator(), denominator * rhs.getNumerator() }.simplify();
  }

  [[nodiscard]] constexpr auto operator*(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return RationalNumber{ numerator * rhs.getNumerator(), denominator * rhs.getDenominator() }.simplify();
  }

  [[nodiscard]] constexpr auto operator+(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return RationalNumber{ numerator * rhs.getDenominator() + (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() }.simplify();
  }

  [[nodiscard]] constexpr auto operator-(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return RationalNumber{ numerator * rhs.getDenominator() - (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() }.simplify();
  }

  [[nodiscard]] constexpr auto getDenominator() const noexcept -> int { return denominator; }

  [[nodiscard]] constexpr auto operator-() const -> RationalNumber { return { numerator * -1, denominator }; }

  [[nodiscard]] constexpr auto getNumerator() const noexcept -> int { return numerator; }

  [[nodiscard]] constexpr auto getFloat() const noexcept -> float
  {
    return ((static_cast<float>(numerator)) / (static_cast<float>(denominator)));
  }

  [[nodiscard]] constexpr auto operator==(const RationalNumber &rhs) const noexcept -> bool {
    return numerator == rhs.numerator && denominator == rhs.denominator;
  }

private:
  int numerator;
  int denominator;
};

#endif