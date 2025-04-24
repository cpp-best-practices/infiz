// infiz.cpp

#include "../libinfiz/Evaluator.hpp"

#include <array>
#include <format>
#include <iostream>

constexpr int max_line = 255;

auto main() -> int
{
  std::array<char, max_line> input{};

  std::cin.getline(input.data(), max_line - 1, '\n');

  while (std::cin.good()) {
    auto result = evaluate(input.data());
    
    if (result) {
      const auto answer = *result;
      std::cout << "answer: ";

      if (answer.getDenominator() == 1) {
        std::cout << std::format("{}\n", answer.getNumerator());
      } else {
        std::cout << std::format(
          "{}/{} ({})\n", answer.getNumerator(), answer.getDenominator(), answer.asFloat<double>());
      }
    } else {
      // Format the error message with the expression and position indicator
      const auto& error = result.error();
      
      // Get error type message
      std::string errorTypeMsg;
      switch (error.type) {
        case EvaluationError::ErrorType::INVALID_NUMBER:
          errorTypeMsg = "Invalid number - expected only digits";
          break;
        case EvaluationError::ErrorType::EMPTY_TOKEN:
          errorTypeMsg = "Empty token encountered";
          break;
        case EvaluationError::ErrorType::STACK_ERROR:
          errorTypeMsg = "Stack error - expression might be malformed";
          break;
        case EvaluationError::ErrorType::INVALID_EXPRESSION:
        default:
          errorTypeMsg = "Invalid expression";
          break;
      }
      
      // Print a visually appealing error with position indicator
      std::cout << "\033[1;31mError:\033[0m " << errorTypeMsg << "\n\n";
      std::cout << "  " << input.data() << "\n";
      std::cout << "  " << std::string(error.position, ' ') << "\033[1;31m^\033[0m\n\n";
    }

    std::cin.getline(input.data(), max_line - 1, '\n');
  }
}
