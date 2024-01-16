#ifndef INFIZ_RATIONAL_NUMBER_H
#define INFIZ_RATIONAL_NUMBER_H

#include <compare>
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
    if (gcd == 0) {
      return *this;
    } else {
      return { numerator / gcd, denominator / gcd };
    }
  }

  [[nodiscard]] constexpr auto operator/(const RationalNumber &rhs) const noexcept
  {
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