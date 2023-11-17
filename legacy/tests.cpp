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

	RationalNumber result = *evaluateExpression(&st);
	assert(result.getDenominator() == expected.getDenominator());
	assert(result.getNumerator() == expected.getNumerator());
	std::cout << "PASS: input: " << input << " output: " << result.getNumerator() << '/' << result.getDenominator() << '\n';
}

int main() {
	run_test("(3 + 2)", RationalNumber(5, 1));
	return 0;
}