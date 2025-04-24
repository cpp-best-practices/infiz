#include <catch2/catch_test_macros.hpp>

#include "../src/libinfiz/Evaluator.hpp"

TEST_CASE("RationalNumber works for constexpr")
{
  // Basic equality and operations
  STATIC_REQUIRE(RationalNumber(4, 1) == RationalNumber(4, 1));
  STATIC_REQUIRE(RationalNumber(4, 1) + RationalNumber(5, 1) == RationalNumber(9, 1));
  STATIC_REQUIRE(RationalNumber(1, 1) / RationalNumber(2, 1) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(1, 2) + RationalNumber(1, 4) == RationalNumber(3, 4));
  
  // Test simplification by explicitly calling simplify()
  STATIC_REQUIRE(RationalNumber(4, 2).simplify() == RationalNumber(2, 1));
  STATIC_REQUIRE(RationalNumber(6, 3).simplify() == RationalNumber(2, 1));
  STATIC_REQUIRE(RationalNumber(10, 15).simplify() == RationalNumber(2, 3));
  
  // Test negative numbers
  STATIC_REQUIRE(RationalNumber(-4, 2).simplify() == RationalNumber(-2, 1));
  STATIC_REQUIRE(RationalNumber(4, -2).simplify() == RationalNumber(-2, 1));
  STATIC_REQUIRE(RationalNumber(-4, -2).simplify() == RationalNumber(2, 1));
  
  // Test more complex operations
  STATIC_REQUIRE(RationalNumber(1, 2) * RationalNumber(2, 3) == RationalNumber(1, 3));
  STATIC_REQUIRE(RationalNumber(1, 2) / RationalNumber(2, 3) == RationalNumber(3, 4));
  STATIC_REQUIRE(RationalNumber(1, 2) - RationalNumber(1, 4) == RationalNumber(1, 4));
  STATIC_REQUIRE(RationalNumber(3, 4) - RationalNumber(1, 2) == RationalNumber(1, 4));
}

TEST_CASE("RationalNumber operator overloads")
{
  // Test operator==
  STATIC_REQUIRE(RationalNumber(1, 2) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(2, 4).simplify() == RationalNumber(1, 2));
  
  // Test operator+
  STATIC_REQUIRE(RationalNumber(1, 3) + RationalNumber(1, 6) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(2, 5) + RationalNumber(1, 5) == RationalNumber(3, 5));
  
  // Test operator-
  STATIC_REQUIRE(RationalNumber(3, 4) - RationalNumber(1, 4) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(1, 2) - RationalNumber(1, 3) == RationalNumber(1, 6));
  
  // Test operator*
  STATIC_REQUIRE(RationalNumber(2, 3) * RationalNumber(3, 4) == RationalNumber(1, 2));
  STATIC_REQUIRE(RationalNumber(1, 2) * RationalNumber(2, 1) == RationalNumber(1, 1));
  
  // Test operator/
  STATIC_REQUIRE(RationalNumber(1, 2) / RationalNumber(1, 4) == RationalNumber(2, 1));
  STATIC_REQUIRE(RationalNumber(3, 4) / RationalNumber(2, 3) == RationalNumber(9, 8));
  
  // Test unary operator-
  STATIC_REQUIRE(-RationalNumber(1, 2) == RationalNumber(-1, 2));
  STATIC_REQUIRE(-RationalNumber(-1, 2) == RationalNumber(1, 2));
}

TEST_CASE("Combinations and Grouping")
{
  STATIC_REQUIRE(evaluate_or_throw("(4 / 2) * 5") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("((1 + 2) + 3) + 4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1 + 2 + 3 + 4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1+2+3+4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("10/2*3") == RationalNumber(15, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("10/(2*3)") == RationalNumber(5, 3));// NOLINT
  
  // More complex expressions
  STATIC_REQUIRE(evaluate_or_throw("(5 + 3) * (2 + 1)") == RationalNumber(24, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(10 / 2) / (3 / 2)") == RationalNumber(10, 3));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1 + 2) * (3 + 4) / (5 + 2)") == RationalNumber(3, 1));// NOLINT
}


TEST_CASE("Nested expressions")
{
  // Multiple nesting levels
  STATIC_REQUIRE(evaluate_or_throw("(((1 + 2) + 3) + 4)") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1 + (2 + (3 + 4)))") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("((1 + 2) * (3 + 4))") == RationalNumber(21, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1 + (2 * (3 + 4)))") == RationalNumber(15, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("((1 + (2 * 3)) + 4)") == RationalNumber(11, 1));// NOLINT
}

TEST_CASE("Addition")
{
  STATIC_REQUIRE(evaluate_or_throw("(3 + 2)") == RationalNumber(5, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(3 + (2 + 4))") == RationalNumber(9, 1));// NOLINT
  
  // Multiple additions
  STATIC_REQUIRE(evaluate_or_throw("1 + 2 + 3 + 4 + 5") == RationalNumber(15, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("10 + 20 + 30") == RationalNumber(60, 1));// NOLINT
  
  // Adding fractions
  STATIC_REQUIRE(evaluate_or_throw("(1/2) + (1/3)") == RationalNumber(5, 6));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1/4) + (1/4) + (1/2)") == RationalNumber(1, 1));// NOLINT
}

TEST_CASE("Subtraction")
{
  STATIC_REQUIRE(evaluate_or_throw("(3 - 2)") == RationalNumber(1, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(3 + (2 - 4))") == RationalNumber(1, 1));// NOLINT
  
  // Multiple subtractions
  STATIC_REQUIRE(evaluate_or_throw("10 - 2 - 3") == RationalNumber(5, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("20 - 5 - 3 - 2") == RationalNumber(10, 1));// NOLINT
  
  // Negative results
  STATIC_REQUIRE(evaluate_or_throw("1 - 5") == RationalNumber(-4, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1/2) - 2") == RationalNumber(-3, 2));// NOLINT
  
  // Subtracting fractions
  STATIC_REQUIRE(evaluate_or_throw("(3/4) - (1/4)") == RationalNumber(1, 2));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(3/4) - (1/2)") == RationalNumber(1, 4));// NOLINT
}

TEST_CASE("Multiplication")
{
  // Basic multiplication
  STATIC_REQUIRE(evaluate_or_throw("(3 * 2)") == RationalNumber(6, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(4 * 5)") == RationalNumber(20, 1));// NOLINT
  
  // Multiple multiplications
  STATIC_REQUIRE(evaluate_or_throw("2 * 3 * 4") == RationalNumber(24, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1 * 2 * 3 * 4") == RationalNumber(24, 1));// NOLINT
  
  // Multiplying with fractions
  STATIC_REQUIRE(evaluate_or_throw("(1/2) * 4") == RationalNumber(2, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1/2) * (1/3)") == RationalNumber(1, 6));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(3/4) * (2/3)") == RationalNumber(1, 2));// NOLINT
}

TEST_CASE("Division")
{
  STATIC_REQUIRE(evaluate_or_throw("(3 / 2)") == RationalNumber(3, 2));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(4 / 2)") == RationalNumber(2, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1 / 2) / 3") == RationalNumber(1, 6));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1 / 2 / 3") == RationalNumber(1, 6));// NOLINT
  
  // Multiple divisions
  STATIC_REQUIRE(evaluate_or_throw("24 / 2 / 3") == RationalNumber(4, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("30 / 3 / 2") == RationalNumber(5, 1));// NOLINT
  
  // Division with larger numbers
  STATIC_REQUIRE(evaluate_or_throw("100 / 25") == RationalNumber(4, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1000 / 250") == RationalNumber(4, 1));// NOLINT
  
  // Division resulting in fractions
  STATIC_REQUIRE(evaluate_or_throw("1 / 3") == RationalNumber(1, 3));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("5 / 2") == RationalNumber(5, 2));// NOLINT
}

TEST_CASE("Order of operations")
{
  // Addition and subtraction
  STATIC_REQUIRE(evaluate_or_throw("1 + 2 - 3") == RationalNumber(0, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("5 - 3 + 2") == RationalNumber(4, 1));// NOLINT
  
  // Multiplication and division
  STATIC_REQUIRE(evaluate_or_throw("2 * 3 / 2") == RationalNumber(3, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("6 / 2 * 3") == RationalNumber(9, 1));// NOLINT
  
  // Mixed operations
  STATIC_REQUIRE(evaluate_or_throw("1 + 2 * 3") == RationalNumber(7, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1 + 4 / 2") == RationalNumber(3, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("2 * 3 + 4") == RationalNumber(10, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("6 / 3 + 2") == RationalNumber(4, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("2 + 3 * 4 + 5") == RationalNumber(19, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("10 / 2 - 3") == RationalNumber(2, 1));// NOLINT
  
  // Parentheses changing order
  STATIC_REQUIRE(evaluate_or_throw("(1 + 2) * 3") == RationalNumber(9, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("2 * (3 + 4)") == RationalNumber(14, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(4 + 6) / 2") == RationalNumber(5, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("10 / (1 + 1)") == RationalNumber(5, 1));// NOLINT
}

TEST_CASE("Large numbers")
{
  // Large integer operations
  STATIC_REQUIRE(evaluate_or_throw("1000 + 2000") == RationalNumber(3000, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("5000 - 3000") == RationalNumber(2000, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("100 * 200") == RationalNumber(20000, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("10000 / 100") == RationalNumber(100, 1));// NOLINT
  
  // Large fractions
  STATIC_REQUIRE(evaluate_or_throw("10000 / 3") == RationalNumber(10000, 3));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1 / 1000) + (1 / 1000)") == RationalNumber(1, 500));// NOLINT
}

TEST_CASE("Using UDL") {
  STATIC_REQUIRE("(3 / 2)"_rn == RationalNumber(3, 2));// NOLINT
  STATIC_REQUIRE("(4 / 2)"_rn == RationalNumber(2, 1));// NOLINT
  STATIC_REQUIRE("(1 / 2) / 3"_rn == RationalNumber(1, 6));// NOLINT
  STATIC_REQUIRE("1 / 2 / 3"_rn == RationalNumber(1, 6));// NOLINT
  
  // More UDL tests
  STATIC_REQUIRE("1+2+3"_rn == RationalNumber(6, 1));// NOLINT
  STATIC_REQUIRE("(1+2)*3"_rn == RationalNumber(9, 1));// NOLINT
  STATIC_REQUIRE("10-5-2"_rn == RationalNumber(3, 1));// NOLINT
  STATIC_REQUIRE("2*(3+4)/2"_rn == RationalNumber(7, 1));// NOLINT
}

TEST_CASE("Using UDL with small fractions")
{
  STATIC_REQUIRE("(1 / 1000000)"_rn == RationalNumber(1, 1000000));// NOLINT
  STATIC_REQUIRE("(1/1000) + (1/1000)"_rn == RationalNumber(1, 500));// NOLINT
  STATIC_REQUIRE("(1/100) * (1/100)"_rn == RationalNumber(1, 10000));// NOLINT
}

TEST_CASE("Complex expressions")
{
  // Mixing multiple operations and parentheses
  STATIC_REQUIRE(evaluate_or_throw("((2 + 3) * 4) - ((6 / 2) + 1)") == RationalNumber(16, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(10 / (2 + 3)) * (7 - 4)") == RationalNumber(6, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("(1 / (1 + 1)) + (1 / (1 + 1 + 1 + 1))") == RationalNumber(3, 4));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("((1 + 2) * (3 + 4)) / ((5 - 3) * (2 + 2))") == RationalNumber(21, 8));// NOLINT
  
  // Long expressions
  STATIC_REQUIRE(evaluate_or_throw("1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10") == RationalNumber(55, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("1 * 2 * 3 * 4 * 5") == RationalNumber(120, 1));// NOLINT
  STATIC_REQUIRE(evaluate_or_throw("100 / 2 / 2 / 5 / 5") == RationalNumber(1, 1));// NOLINT
}