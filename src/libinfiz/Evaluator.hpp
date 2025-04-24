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

// Evaluation errors with position information
struct EvaluationError {
  enum class ErrorType {
    INVALID_NUMBER,    // Invalid character in number
    INVALID_EXPRESSION, // General parsing error
    EMPTY_TOKEN,       // Empty token found
    STACK_ERROR        // Error with the stack operations
  };
  
  ErrorType type;
  size_t position; // Position in the expression where the error occurred
  
  constexpr EvaluationError(ErrorType t, size_t pos = 0) : type(t), position(pos) {}
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
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      numbers.push(*operand1_result + *operand2_result);
      break;
    }

    case Operators::MINUS_SIGN: {
      operators.pop();
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      numbers.push(*operand1_result - *operand2_result);
      break;
    }

    case Operators::MULTIPLY_SIGN: {
      operators.pop();
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      numbers.push(*operand1_result * *operand2_result);
      break;
    }

    case Operators::DIVIDE_SIGN: {
      operators.pop();
      auto operand2_result = numbers.pop();
      if (!operand2_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
      }
      
      auto operand1_result = numbers.pop();
      if (!operand1_result) {
        return std::unexpected(EvaluationError(EvaluationError::ErrorType::STACK_ERROR));
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

  for (size_t i = 0; i < input.size(); ++i) {
    const char digit = input[i];
    result *= 10;// NOLINT

    if (digit >= '0' && digit <= '9') { 
      result += static_cast<Type>(digit - '0'); 
    } else {
      // Return position information with the error
      return std::unexpected(EvaluationError(
        EvaluationError::ErrorType::INVALID_NUMBER, 
        i));
    }
  }

  return result;
}

[[nodiscard]] constexpr auto evaluateExpression(StringTokenizer &tokenizer) 
  -> std::expected<RationalNumber, EvaluationError>
{
  Stack<Operators> operators;
  Stack<RationalNumber> numbers;

  // Creates an error with the current tokenizer position
  const auto make_error = [&tokenizer](EvaluationError::ErrorType type) -> EvaluationError {
    return EvaluationError(type, tokenizer.offset());
  };
  
  // Track parenthesis balance to detect mismatches
  int parenthesis_count = 0;

  const auto evalStacks = [&]() -> std::expected<void, EvaluationError> {
    auto result = ::evaluateStacks(numbers, operators);
    if (!result) {
      return std::unexpected(make_error(result.error().type));
    }
    return {};
  };

  while (tokenizer.hasMoreTokens()) {
    auto next = tokenizer.nextToken();

    if (next.empty()) { 
      return std::unexpected(EvaluationError(EvaluationError::ErrorType::EMPTY_TOKEN, tokenizer.offset())); 
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
        parenthesis_count--; // Decrement for closing parenthesis
        // Check for negative count (more closing than opening parentheses)
        if (parenthesis_count < 0) {
          return std::unexpected(EvaluationError(EvaluationError::ErrorType::INVALID_EXPRESSION, tokenizer.offset() - 1));
        }
        operation = true;
        break;
      case '(':
        value = Operators::OPEN_PAREN;
        parenthesis_count++; // Increment open parenthesis count
        operation = true;
        break;

      default:
        operation = false;
        auto parsed_result = from_chars<int>(next);
        if (!parsed_result) {
          return std::unexpected(parsed_result.error());
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
          // Check if the top of the stack is an opening parenthesis (empty parentheses case)
          if (operators.peek() != nullptr && *operators.peek() == Operators::OPEN_PAREN) {
            // Empty parentheses like () or part of (()) - not valid in this calculator
            return std::unexpected(EvaluationError(EvaluationError::ErrorType::INVALID_EXPRESSION, tokenizer.offset() - 1));
          }
          
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

  // Check for unbalanced parentheses
  if (parenthesis_count > 0) {
    return std::unexpected(EvaluationError(EvaluationError::ErrorType::INVALID_EXPRESSION, tokenizer.offset()));
  }
  
  if (!operators.empty() || tokenizer.hasUnparsedInput()) {
    return std::unexpected(EvaluationError(EvaluationError::ErrorType::INVALID_EXPRESSION, tokenizer.offset()));
  }

  if (numbers.peek() != nullptr) {
    return *numbers.peek();
  }

  return std::unexpected(EvaluationError(EvaluationError::ErrorType::INVALID_EXPRESSION, tokenizer.offset()));
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