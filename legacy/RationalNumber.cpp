//RationalNumber.h

#include "RationalNumber.h"

RationalNumber::RationalNumber(int num, int den)
	: numerator(num), denominator(den)
{
}

RationalNumber RationalNumber::operator/(const RationalNumber & rn) const {
	return RationalNumber(
		numerator * rn.getDenominator(),
		denominator * rn.getNumerator()
		);
}

RationalNumber RationalNumber::operator*(const RationalNumber & rn) const {
	return RationalNumber(
		numerator * rn.getNumerator(),
		denominator * rn.getDenominator());
}

RationalNumber RationalNumber::operator+(const RationalNumber &rn) const {
	int denom = denominator * rn.getDenominator();
	int numerator = this->numerator * rn.getDenominator();
	int numer = numerator + (rn.getNumerator() * denominator);

	return RationalNumber(numer, denom);
}

RationalNumber RationalNumber::operator-(const RationalNumber &rn) const {
	int denom = denominator * rn.getDenominator();
	
	int numerator = this->numerator * rn.getDenominator();
	int numer = numerator - (rn.getNumerator() * denominator);

	return RationalNumber(numer, denom);
}

int RationalNumber::getDenominator() const {
	return denominator;
}

RationalNumber RationalNumber::operator-() const {
	return RationalNumber(numerator * -1, denominator);
}

int RationalNumber::getNumerator() const {
	return numerator;
}

float RationalNumber::getFloat() {
	return ( (static_cast<float>(numerator)) / (static_cast<float>(denominator)) );
}

