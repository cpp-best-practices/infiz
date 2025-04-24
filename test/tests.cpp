
#include <iostream>
#include <catch2/catch_test_macros.hpp>

#include "../src/libinfiz/Evaluator.hpp"

TEST_CASE("Error handling with std::expected")
{
  // Just test that invalid inputs result in errors
  auto result = evaluate("abc");
  REQUIRE(!result);
  
  result = evaluate("(3 + )");
  REQUIRE(!result);
  
  result = evaluate("(3 + 4");
  REQUIRE(!result);
  
  // Test for successful evaluation
  result = evaluate("3 + 4");
  REQUIRE(result);
  REQUIRE(*result == RationalNumber(7, 1));
}

