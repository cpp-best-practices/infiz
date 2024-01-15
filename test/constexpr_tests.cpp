#include <catch2/catch_test_macros.hpp>

#include "../src/libinfiz/Evaluator.hpp"

TEST_CASE("RationalNumber works for constexpr")
{
  STATIC_REQUIRE(RationalNumber(4, 1) == RationalNumber(4, 1));
  STATIC_REQUIRE(RationalNumber(4, 1) + RationalNumber(5, 1) == RationalNumber(9, 1));
  STATIC_REQUIRE(RationalNumber(1, 1) / RationalNumber(2, 1) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(1, 2) + RationalNumber(1, 4) == RationalNumber(3, 4));
}
