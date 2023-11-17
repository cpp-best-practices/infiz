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
	~RationalNumber();
	void divide(RationalNumber * rn);
	void multiply(RationalNumber * rn);
	void add(RationalNumber * rn);
	void subtract(RationalNumber * rn);
	void negate();

	int getNumerator();
	int getDenominator();

	float getFloat();
	
private:
	int numerator;
	int denominator;
};

#endif