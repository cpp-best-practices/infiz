#ifndef INFIZ_RATIONAL_NUMBER_H
#define INFIZ_RATIONAL_NUMBER_H

// RationalNumber.h

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

  constexpr auto operator/(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return { numerator * rhs.getDenominator(), denominator * rhs.getNumerator() };
  }

  constexpr auto operator*(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return { numerator * rhs.getNumerator(), denominator * rhs.getDenominator() };
  }

  constexpr auto operator+(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return { numerator * rhs.getDenominator() + (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() };
  }

  constexpr auto operator-(const RationalNumber &rhs) const noexcept -> RationalNumber
  {
    return { numerator * rhs.getDenominator() - (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() };
  }

  constexpr auto getDenominator() const noexcept -> int { return denominator; }

  constexpr auto operator-() const -> RationalNumber { return { numerator * -1, denominator }; }

  constexpr auto getNumerator() const noexcept -> int { return numerator; }

  constexpr auto getFloat() const noexcept -> float
  {
    return ((static_cast<float>(numerator)) / (static_cast<float>(denominator)));
  }

  constexpr auto operator==(const RationalNumber &rhs) const noexcept -> bool {
    return numerator == rhs.numerator && denominator == rhs.denominator;
  }

private:
  int numerator;
  int denominator;
};

#endif