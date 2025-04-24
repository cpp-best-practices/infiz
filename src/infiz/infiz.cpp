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
      std::cout << result.error().message << '\n';
    }

    std::cin.getline(input.data(), max_line - 1, '\n');
  }
}
