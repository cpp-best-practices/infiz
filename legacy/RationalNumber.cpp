//RationalNumber.h

#include "RationalNumber.h"

RationalNumber::RationalNumber(int num, int den) {
	numerator = num;
	denominator = den;
}

void RationalNumber::divide(const RationalNumber & rn) {
	denominator *= rn.getNumerator();
	numerator *= rn.getDenominator();
}

void RationalNumber::multiply(const RationalNumber & rn) {
	numerator *= rn.getNumerator();
	denominator *= rn.getDenominator();
}

void RationalNumber::add(const RationalNumber &rn) {
	int denom = denominator * rn.getDenominator();
	numerator *= rn.getDenominator();
	int numer = numerator + (rn.getNumerator() * denominator);

	numerator = numer;
	denominator = denom;
}

void RationalNumber::subtract(const RationalNumber &rn) {
	int denom = denominator * rn.getDenominator();
	
	numerator *= rn.getDenominator();
	int numer = numerator - (rn.getNumerator() * denominator);

	numerator = numer;
	denominator = denom;
}

int RationalNumber::getDenominator() const {
	return denominator;
}

void RationalNumber::negate() {
	numerator*=-1;
}

int RationalNumber::getNumerator() const {
	return numerator;
}

float RationalNumber::getFloat() {
	return ( ((float)numerator) / ((float)denominator) );
}

