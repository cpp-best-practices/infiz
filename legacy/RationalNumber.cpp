//RationalNumber.h

#include "RationalNumber.h"

RationalNumber::RationalNumber(int num, int den) {
	numerator = num;
	denominator = den;
}

RationalNumber::~RationalNumber() {
}

void RationalNumber::divide(RationalNumber * rn) {
	denominator *= rn->getNumerator();
	numerator *= rn->getDenominator();
}

void RationalNumber::multiply(RationalNumber * rn) {
	numerator *= rn->getNumerator();
	denominator *= rn->getDenominator();
}

void RationalNumber::add(RationalNumber * rn) {
	int denom = denominator * rn->getDenominator();
	numerator *= rn->getDenominator();
	int numer = numerator + (rn->getNumerator() * denominator);

	numerator = numer;
	denominator = denom;
}

void RationalNumber::subtract(RationalNumber * rn) {
	int denom = denominator * rn->getDenominator();
	
	numerator *= rn->getDenominator();
	int numer = numerator - (rn->getNumerator() * denominator);

	numerator = numer;
	denominator = denom;
}

int RationalNumber::getDenominator() {
	return denominator;
}

void RationalNumber::negate() {
	numerator*=-1;
}

int RationalNumber::getNumerator() {
	return numerator;
}

float RationalNumber::getFloat() {
	return ( ((float)numerator) / ((float)denominator) );
}

