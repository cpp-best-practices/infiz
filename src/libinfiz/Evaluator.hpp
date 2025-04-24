#ifndef INFIZ_EVALUATOR_HPP
#define INFIZ_EVALUATOR_HPP

#include "RationalNumber.hpp"
#include "Stack.hpp"
#include "StringTokenizer.hpp"
#include <concepts>
#include <string_view>
#include <format>
#include <expected>
#include <stdexcept>

enum struct Operators { PLUS_SIGN, CLOSE_PAREN, OPEN_PAREN, MINUS_SIGN, DIVIDE_SIGN, MULTIPLY_SIGN };

struct EvaluationError {
  enum class ErrorType {
    INVALID_NUMBER,
    INVALID_EXPRESSION,
    EMPTY_TOKEN,
    STACK_EMPTY
  };
  
  ErrorType type;
  std::string message;
  
  constexpr EvaluationError(ErrorType t, std::string_view msg) : type(t), message(msg) {}
};

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


constexpr auto evaluateStacks(Stack<RationalNumber> &numbers, Stack<Operators> &operators) 
  -> std::expected<void, EvaluationError>
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
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing second operand for + operation: {}", operand2_result.error().message)));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing first operand for + operation: {}", operand1_result.error().message)));
      }
      
      numbers.push(*operand1_result + *operand2_result);
      break;
    }

    case Operators::MINUS_SIGN: {
      operators.pop();
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing second operand for - operation: {}", operand2_result.error().message)));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing first operand for - operation: {}", operand1_result.error().message)));
      }
      
      numbers.push(*operand1_result - *operand2_result);
      break;
    }

    case Operators::MULTIPLY_SIGN: {
      operators.pop();
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing second operand for * operation: {}", operand2_result.error().message)));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing first operand for * operation: {}", operand1_result.error().message)));
      }
      
      numbers.push(*operand1_result * *operand2_result);
      break;
    }

    case Operators::DIVIDE_SIGN: {
      operators.pop();
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing second operand for / operation: {}", operand2_result.error().message)));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(
          EvaluationError::ErrorType::STACK_EMPTY,
          std::format("Missing first operand for / operation: {}", operand1_result.error().message)));
      }
      
      numbers.push(*operand1_result / *operand2_result);
      break;
    }

    case Operators::CLOSE_PAREN:
      break;// we want to continue
    }
  }
  
  return {};
}


template<std::integral Type> 
[[nodiscard]] constexpr auto from_chars(std::string_view input) -> std::expected<Type, EvaluationError>
{
  Type result{ 0 };

  for (const char digit : input) {
    result *= 10;// NOLINT

    if (digit >= '0' && digit <= '9') { 
      result += static_cast<Type>(digit - '0'); 
    } else {
      return std::unexpected(EvaluationError(
        EvaluationError::ErrorType::INVALID_NUMBER, 
        std::format("Invalid digit '{}' in number", digit)));
    }
  }

  return result;
}

[[nodiscard]] constexpr auto evaluateExpression(StringTokenizer &tokenizer) 
  -> std::expected<RationalNumber, EvaluationError>
{
  Stack<Operators> operators;
  Stack<RationalNumber> numbers;

  const auto make_error = [&tokenizer](EvaluationError::ErrorType type, std::string_view msg = "") -> EvaluationError {
    std::string contextual_message = std::format(
      R"(Unable to evaluate expression
{}
{}^ unevaluated)",
      tokenizer.input(),
      std::string(tokenizer.offset(), ' '));
    
    if (!msg.empty()) {
      contextual_message = std::format("{}: {}", contextual_message, msg);
    }
    
    return EvaluationError(type, contextual_message);
  };

  const auto evalStacks = [&]() -> std::expected<void, EvaluationError> {
    auto result = ::evaluateStacks(numbers, operators);
    if (!result) {
      return std::unexpected(make_error(result.error().type, result.error().message));
    }
    return {};
  };

  while (tokenizer.hasMoreTokens()) {
    auto next = tokenizer.nextToken();

    if (next.empty()) { 
      return std::unexpected(make_error(EvaluationError::ErrorType::EMPTY_TOKEN)); 
    }

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
        auto parsed_result = from_chars<int>(next);
        if (!parsed_result) {
          return std::unexpected(make_error(parsed_result.error().type, parsed_result.error().message));
        }
        numbers.emplace(*parsed_result, 1);
        break;
      }

      if (operation) {
        switch (value) {
        case Operators::OPEN_PAREN: {
          operators.push(value);
          break;
        }
        case Operators::CLOSE_PAREN: {
          operators.push(value);
          auto eval_result = evalStacks();
          if (!eval_result) {
            return std::unexpected(eval_result.error());
          }
          break;
        }
        case Operators::PLUS_SIGN:
        case Operators::MINUS_SIGN:
        case Operators::MULTIPLY_SIGN:
        case Operators::DIVIDE_SIGN: {
          if (operators.peek() != nullptr && precedence(value) <= precedence(*operators.peek())) { 
            auto eval_result = evalStacks();
            if (!eval_result) {
              return std::unexpected(eval_result.error());
            }
          }
          operators.push(value);
          break;
        }
        }
      }
    }
  }

  if (operators.peek() != nullptr) { 
    auto eval_result = evalStacks();
    if (!eval_result) {
      return std::unexpected(eval_result.error());
    }
  }

  if (!operators.empty() || tokenizer.hasUnparsedInput()) {
    return std::unexpected(make_error(EvaluationError::ErrorType::INVALID_EXPRESSION));
  }

  if (numbers.peek() != nullptr) {
    return *numbers.peek();
  }

  return std::unexpected(make_error(EvaluationError::ErrorType::INVALID_EXPRESSION));
}

[[nodiscard]] constexpr auto evaluate(std::string_view input) -> std::expected<RationalNumber, EvaluationError>
{
  StringTokenizer tokenizer(input);
  return evaluateExpression(tokenizer);
}

consteval auto evaluate_or_throw(std::string_view input) -> RationalNumber
{
  StringTokenizer tokenizer(input);
  auto result = evaluateExpression(tokenizer);
  if (!result) {
    // During compile-time evaluation, we can't do much better than a generic error message
    throw std::runtime_error("Invalid expression during consteval");
  }
  return *result;
}

consteval auto operator""_rn(const char *str, std::size_t len) -> RationalNumber
{
  return evaluate_or_throw(std::string_view(str, len));
}


#endif