#ifndef INFIZ_RATIONAL_NUMBER_H
#define INFIZ_RATIONAL_NUMBER_H

//RationalNumber.h

/**
 * A Class that stores the numerator and denominator
 * of a rational number.
 */

class RationalNumber {
public:
	RationalNumber(int num, int den);
	void divide(const RationalNumber & rn);
	void multiply(const RationalNumber & rn);
	void add(const RationalNumber & rn);
	void subtract(const RationalNumber & rn);
	void negate();

	int getNumerator() const;
	int getDenominator() const;

	float getFloat();
	
private:
	int numerator;
	int denominator;
};

#endif