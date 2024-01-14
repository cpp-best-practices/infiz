// RationalNumber.h

#include "RationalNumber.h"

RationalNumber::RationalNumber(int num, int den)// NOLINT
  : numerator(num), denominator(den)
{}

RationalNumber RationalNumber::operator/(const RationalNumber &rhs) const
{
  return RationalNumber(// NOLINT
    numerator * rhs.getDenominator(),
    denominator * rhs.getNumerator());
}

RationalNumber RationalNumber::operator*(const RationalNumber &rhs) const
{
  return RationalNumber(// NOLINT
    numerator * rhs.getNumerator(),
    denominator * rhs.getDenominator());
}

RationalNumber RationalNumber::operator+(const RationalNumber &rhs) const
{
  const int denom = denominator * rhs.getDenominator();
  const int new_numerator = this->numerator * rhs.getDenominator();
  const int numer = new_numerator + (rhs.getNumerator() * denominator);

  return RationalNumber(numer, denom);// NOLINT
}

RationalNumber RationalNumber::operator-(const RationalNumber &rhs) const
{
  const int denom = denominator * rhs.getDenominator();

  const int new_numerator = this->numerator * rhs.getDenominator();
  const int numer = new_numerator - (rhs.getNumerator() * denominator);

  return RationalNumber(numer, denom);// NOLINT
}

int RationalNumber::getDenominator() const { return denominator; }

RationalNumber RationalNumber::operator-() const
{
  return RationalNumber(numerator * -1, denominator);// NOLINT
}

int RationalNumber::getNumerator() const { return numerator; }

float RationalNumber::getFloat() const { return ((static_cast<float>(numerator)) / (static_cast<float>(denominator))); }
