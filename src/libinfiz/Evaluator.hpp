#ifndef INFIZ_EVALUATOR_HPP
#define INFIZ_EVALUATOR_HPP

#include "RationalNumber.hpp"
#include "Stack.hpp"
#include "StringTokenizer.hpp"
#include <string_view>
#include <concepts>

enum struct Operators { PLUS_SIGN, CLOSE_PAREN, OPEN_PAREN, MINUS_SIGN, DIVIDE_SIGN, MULTIPLY_SIGN };

constexpr auto precedence(Operators input) noexcept -> int
{
  switch (input) {
  case Operators::CLOSE_PAREN:
    return 3;
  case Operators::PLUS_SIGN:
  case Operators::MINUS_SIGN:
    return 1;
  case Operators::MULTIPLY_SIGN:
  case Operators::DIVIDE_SIGN:
    return 2;
  case Operators::OPEN_PAREN:
    return 0;
  }

  return 0;
}


constexpr void evaluateStacks(Stack<RationalNumber> &numbers, Stack<Operators> &operators)
{
  bool eatOpenParen = false;
  bool cont = true;

  if (!operators.empty() && *operators.peek() == Operators::CLOSE_PAREN) {
    eatOpenParen = true;
    operators.pop();
  }

  while (operators.peek() != nullptr && cont) {

    switch (*operators.peek()) {
    case Operators::OPEN_PAREN:
      if (eatOpenParen) {
        operators.pop();
        cont = false;
      } else {
        cont = false;
      }

      break;

    case Operators::PLUS_SIGN: {
      operators.pop();
      const auto operand2 = numbers.pop();
      const auto operand1 = numbers.pop();
      numbers.push(operand1 + operand2);
      break;
    }

    case Operators::MINUS_SIGN: {
      operators.pop();
      numbers.push(-numbers.pop());
      break;
    }

    case Operators::MULTIPLY_SIGN: {
      operators.pop();
      const auto operand2 = numbers.pop();
      const auto operand1 = numbers.pop();
      numbers.push(operand1 * operand2);
      break;
    }

    case Operators::DIVIDE_SIGN: {
      operators.pop();
      const auto operand2 = numbers.pop();
      const auto operand1 = numbers.pop();
      numbers.push(operand1 / operand2);
      break;
    }

    case Operators::CLOSE_PAREN:
      break;// we want to continue
    }
  }
}


template<std::integral Type>
[[nodiscard]] constexpr auto from_chars(std::string_view input) -> Type
{
  Type result{0};

  for (const char digit : input) {
    result *= 10; // NOLINT

    if (digit >= '0' && digit <= '9') {
      result += static_cast<Type>(digit - '0');
    }
  }

  return result;
}

[[nodiscard]] constexpr auto evaluateExpression(StringTokenizer &tokenizer) -> RationalNumber
{
  Stack<Operators> operators;
  Stack<RationalNumber> numbers;

  while (tokenizer.hasMoreTokens()) {

    auto next = tokenizer.nextToken();

    auto value = Operators::PLUS_SIGN;

    if (!next.empty()) {
      auto operation = false;
      switch (next[0]) {
      case '+':
        value = Operators::PLUS_SIGN;
        operation = true;
        break;
      case '/':
        value = Operators::DIVIDE_SIGN;
        operation = true;
        break;
      case '-':
        value = Operators::MINUS_SIGN;
        operation = true;
        break;
      case '*':
        value = Operators::MULTIPLY_SIGN;
        operation = true;
        break;
      case ')':
        value = Operators::CLOSE_PAREN;
        operation = true;
        break;
      case '(':
        value = Operators::OPEN_PAREN;
        operation = true;
        break;

      default:
        operation = false;
        const std::integral auto parsed = from_chars<int>(next);
        numbers.emplace(parsed, 1);
        break;
      }

      if (operation) {
        switch (value) {
        case Operators::OPEN_PAREN:
          operators.push(value);
          break;
        case Operators::CLOSE_PAREN:
          operators.push(value);
          evaluateStacks(numbers, operators);
          break;
        default:
          if (operators.peek() != nullptr && precedence(value) <= precedence(*operators.peek())) {
            evaluateStacks(numbers, operators);
          }
          operators.push(value);
          break;
        }
      }
    }
  }

  if (operators.peek() != nullptr) { evaluateStacks(numbers, operators); }

  if (numbers.peek() != nullptr) {
    return *numbers.peek();
  } else {
    return { 0, 0 };
  }
}

[[nodiscard]] constexpr auto evaluate(std::string_view input) -> RationalNumber
{
  StringTokenizer tokenizer(input);
  return evaluateExpression(tokenizer);
}

consteval auto operator""_rn(const char *str, std::size_t len) -> RationalNumber
{
  return evaluate(std::string_view(str, len));
}


#endif