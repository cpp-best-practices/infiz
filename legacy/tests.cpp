// ensure that asserts run regardless of build settings
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>

#include "StringTokenizer.h"
#include "Stack.h"
#include "RationalNumber.h"
#include "Evaluator.hpp"


void run_test(const std::string &input, RationalNumber expected)
{
	StringTokenizer st(input);
	RationalNumber result = evaluateExpression(st);

	if (result.getDenominator() != expected.getDenominator() ||
		result.getNumerator() != expected.getNumerator()) {
		std::cout << "FAIL: ";
	} else {
		std::cout << "PASS: ";
	}

	std::cout << "input: " << input 
		<< " expected: "  << expected.getNumerator() << '/' << expected.getDenominator() 
		<< " got: " << result.getNumerator() << '/' << result.getDenominator() << '\n';
}

int main() {
	run_test("(3 + 2)", RationalNumber(5, 1));
	run_test("(3 / 2)", RationalNumber(3, 2));
	run_test("(4 / 2)", RationalNumber(4, 2));
	run_test("(4 / 2) * 5", RationalNumber(20, 2));
	run_test("(1 / 2) / 3", RationalNumber(1, 6));
	run_test("((1 + 2) + 3) + 4", RationalNumber(10, 1));


	// these fail because we expect grouping into 2's
	run_test("1 / 2 / 3", RationalNumber(3, 2));
	run_test("1 + 2 + 3 + 4", RationalNumber(10, 1));
	return 0;
}