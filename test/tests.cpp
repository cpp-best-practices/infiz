
#include <iostream>
#include <catch2/catch_test_macros.hpp>

#include "../src/libinfiz/Evaluator.hpp"



TEST_CASE("Addition")
{
  CHECK(evaluate("(3 + 2)") == RationalNumber(5, 1));// NOLINT
  CHECK(evaluate("(3 + (2 + 4))") == RationalNumber(9, 1));// NOLINT
}

TEST_CASE("Division")
{
  CHECK(evaluate("(3 / 2)")== RationalNumber(3, 2));// NOLINT
  CHECK(evaluate("(4 / 2)") == RationalNumber(2, 1) );// NOLINT
  CHECK(evaluate("(1 / 2) / 3") == RationalNumber(1, 6) );// NOLINT
  CHECK(evaluate("1 / 2 / 3") == RationalNumber(1, 6) );// NOLINT
}

TEST_CASE("Combinations and Grouping")
{
  CHECK(evaluate("(4 / 2) * 5") == RationalNumber(10, 1));// NOLINT
  CHECK(evaluate("((1 + 2) + 3) + 4")== RationalNumber(10, 1));// NOLINT
  CHECK(evaluate("1 + 2 + 3 + 4")== RationalNumber(10, 1));// NOLINT
  CHECK(evaluate("1+2+3+4")== RationalNumber(10, 1));// NOLINT
  CHECK(evaluate("10/2*3") == RationalNumber(15, 1));// NOLINT
  CHECK(evaluate("10/(2*3)") ==  RationalNumber(5, 3));// NOLINT
}

