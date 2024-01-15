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

  constexpr RationalNumber operator/(const RationalNumber &rhs) const noexcept
  {
    return { numerator * rhs.getDenominator(), denominator * rhs.getNumerator() };
  }

  constexpr RationalNumber operator*(const RationalNumber &rhs) const noexcept
  {
    return { numerator * rhs.getNumerator(), denominator * rhs.getDenominator() };
  }

  constexpr RationalNumber operator+(const RationalNumber &rhs) const noexcept
  {
    return { numerator * rhs.getDenominator() + (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() };
  }

  constexpr RationalNumber operator-(const RationalNumber &rhs) const noexcept
  {
    return { numerator * rhs.getDenominator() - (rhs.getNumerator() * denominator),
      denominator * rhs.getDenominator() };
  }

  constexpr int getDenominator() const noexcept { return denominator; }

  constexpr RationalNumber operator-() const { return { numerator * -1, denominator }; }

  constexpr int getNumerator() const noexcept { return numerator; }

  constexpr float getFloat() const noexcept
  {
    return ((static_cast<float>(numerator)) / (static_cast<float>(denominator)));
  }

private:
  int numerator;
  int denominator;
};

#endif