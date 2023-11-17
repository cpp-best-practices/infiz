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


void run_test(const char *input, RationalNumber expected)
{
	// Possible UB, const_cast, but we need to capture the state
	// then fix later!
	StringTokenizer st(const_cast<char *>(input));

	// these will have to change once I make the code correct without heap everywhere

	// why you used the heap:
	//  * stack was too small! (not right!)
	//  * that's just how we did it back then! (but that's still bad practice even then!)
	// 
	// actual reasons:
	//  * I didn't understand copy constructors
	//  * I didn't use stdlib
	//  * I was learning Java also at that time
    //  * I don't recall professors ever discussing memory leaks or efficiency!

	RationalNumber *result = evaluateExpression(&st);
	if (result->getDenominator() != expected.getDenominator() ||
		result->getNumerator() != expected.getNumerator()) {
		std::cout << "FAIL: ";
	} else {
		std::cout << "PASS: ";
	}

	std::cout << "input: " << input 
		<< " expected: "  << expected.getNumerator() << '/' << expected.getDenominator() 
		<< " got: " << result->getNumerator() << '/' << result->getDenominator() << '\n';
}

int main() {
	run_test("(3 + 2)", RationalNumber(5, 1));
	run_test("(3 / 2)", RationalNumber(3, 2));
	run_test("(4 / 2)", RationalNumber(4, 2));
	run_test("(4 / 2) * 5", RationalNumber(20, 2));

	// we need to evaluate this for later, I don't think
	// this is correct, but we're capturing the current state of things.
	run_test("1 / 2 / 3", RationalNumber(3, 2));
	return 0;
}