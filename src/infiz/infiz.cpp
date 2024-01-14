// infiz.cpp

#include "../libinfiz/Evaluator.hpp"
#include "../libinfiz/RationalNumber.h"
#include "../libinfiz/Stack.h"
#include "../libinfiz/StringTokenizer.h"

#include <cstdlib>
#include <iostream>

const int max_line = 255;

int main(int /*argc*/, char * /*args*/[])
{

  char input[max_line];// NOLINT

  std::cin.getline(static_cast<char *>(input), max_line - 1, '\n');

  while (std::cin.good()) {
    StringTokenizer tokenizer(static_cast<const char *>(input));
    const RationalNumber answer = evaluateExpression(tokenizer);
    std::cout << "answer: ";

    if (answer.getDenominator() == 1) {
      std::cout << answer.getNumerator() << '\n';
    } else {
      std::cout << answer.getNumerator() << '/' << answer.getDenominator() << " (" << answer.getFloat() << ")" << '\n';
    }

    std::cin.getline(static_cast<char *>(input), max_line - 1, '\n');
  }
}
