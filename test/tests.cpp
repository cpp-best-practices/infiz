// ensure that asserts run regardless of build settings
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>

#include "../src/libinfiz/Evaluator.hpp"


void run_test(const std::string &input, RationalNumber expected, bool &success)
{
	StringTokenizer tokenizer(input);
	const RationalNumber result = evaluateExpression(tokenizer);


	if (result.getDenominator() != expected.getDenominator() ||
		result.getNumerator() != expected.getNumerator()) {
		success = false;
		std::cout << "FAIL: ";
	} else {
		std::cout << "PASS: ";
	}

	std::cout << "input: " << input 
		<< " expected: "  << expected.getNumerator() << '/' << expected.getDenominator() 
		<< " got: " << result.getNumerator() << '/' << result.getDenominator() << '\n';
}

int main() {
	bool all_passed = true;

	run_test("(3 + 2)", RationalNumber(5, 1), all_passed); // NOLINT
	run_test("(3 / 2)", RationalNumber(3, 2), all_passed);// NOLINT
	run_test("(4 / 2)", RationalNumber(4, 2), all_passed);// NOLINT
	run_test("(4 / 2) * 5", RationalNumber(20, 2), all_passed);// NOLINT
	run_test("(1 / 2) / 3", RationalNumber(1, 6), all_passed);// NOLINT
	run_test("((1 + 2) + 3) + 4", RationalNumber(10, 1), all_passed);// NOLINT

	run_test("1 / 2 / 3", RationalNumber(1, 6), all_passed);// NOLINT
	run_test("1 + 2 + 3 + 4", RationalNumber(10, 1), all_passed);// NOLINT
	run_test("1+2+3+4", RationalNumber(10, 1), all_passed);// NOLINT
	run_test("10/2*3", RationalNumber(30, 2), all_passed);// NOLINT
	run_test("10/(2*3)", RationalNumber(10, 6), all_passed);// NOLINT

	if (all_passed) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}