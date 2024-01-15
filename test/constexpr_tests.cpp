#include <catch2/catch_test_macros.hpp>

#include "../src/libinfiz/Evaluator.hpp"

TEST_CASE("RationalNumber works for constexpr")
{
  STATIC_REQUIRE(RationalNumber(4, 1) == RationalNumber(4, 1));
  STATIC_REQUIRE(RationalNumber(4, 1) + RationalNumber(5, 1) == RationalNumber(9, 1));
  STATIC_REQUIRE(RationalNumber(1, 1) / RationalNumber(2, 1) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(1, 2) + RationalNumber(1, 4) == RationalNumber(3, 4));
}


TEST_CASE("Combinations and Grouping")
{
  STATIC_REQUIRE(evaluate("(4 / 2) * 5") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate("((1 + 2) + 3) + 4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate("1 + 2 + 3 + 4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate("1+2+3+4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate("10/2*3") == RationalNumber(15, 1));// NOLINT
  STATIC_REQUIRE(evaluate("10/(2*3)") == RationalNumber(5, 3));// NOLINT
}


TEST_CASE("Addition")
{
  STATIC_REQUIRE(evaluate("(3 + 2)") == RationalNumber(5, 1));// NOLINT
  STATIC_REQUIRE(evaluate("(3 + (2 + 4))") == RationalNumber(9, 1));// NOLINT
}

TEST_CASE("Division")
{
  STATIC_REQUIRE(evaluate("(3 / 2)") == RationalNumber(3, 2));// NOLINT
  STATIC_REQUIRE(evaluate("(4 / 2)") == RationalNumber(2, 1));// NOLINT
  STATIC_REQUIRE(evaluate("(1 / 2) / 3") == RationalNumber(1, 6));// NOLINT
  STATIC_REQUIRE(evaluate("1 / 2 / 3") == RationalNumber(1, 6));// NOLINT
}

TEST_CASE("Using UDL") {
  STATIC_REQUIRE("(3 / 2)"_rn == RationalNumber(3, 2));// NOLINT
  STATIC_REQUIRE("(4 / 2)"_rn == RationalNumber(2, 1));// NOLINT
  STATIC_REQUIRE("(1 / 2) / 3"_rn == RationalNumber(1, 6));// NOLINT
  STATIC_REQUIRE("1 / 2 / 3"_rn == RationalNumber(1, 6));// NOLINT
}


TEST_CASE("Using UDL with small fractions")
{
  STATIC_REQUIRE("(1 / 1000000)"_rn == RationalNumber(1, 1000000));// NOLINT
}