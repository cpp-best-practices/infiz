// infiz.cpp

#include "../libinfiz/Evaluator.hpp"

#include <array>
#include <iostream>

constexpr int max_line = 255;

int main(int /*argc*/, char * /*args*/[])
{
  std::array<char, max_line> input{};

  std::cin.getline(input.data(), max_line - 1, '\n');

  while (std::cin.good()) {
    StringTokenizer tokenizer(input.data());
    const auto answer = evaluateExpression(tokenizer);
    std::cout << "answer: ";

    if (answer.getDenominator() == 1) {
      std::cout << answer.getNumerator() << '\n';
    } else {
      std::cout << answer.getNumerator() << '/' << answer.getDenominator() << " (" << answer.getFloat() << ")" << '\n';
    }

    std::cin.getline(input.data(), max_line - 1, '\n');
  }
}
