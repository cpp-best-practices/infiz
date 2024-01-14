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
  RationalNumber(int num, int den);
  RationalNumber operator/(const RationalNumber &rhs) const;
  RationalNumber operator*(const RationalNumber &rhs) const;
  RationalNumber operator+(const RationalNumber &rhs) const;
  RationalNumber operator-(const RationalNumber &rhs) const;
  RationalNumber operator-() const;

  int getNumerator() const;
  int getDenominator() const;

  float getFloat() const;

private:
  int numerator;
  int denominator;
};

#endif