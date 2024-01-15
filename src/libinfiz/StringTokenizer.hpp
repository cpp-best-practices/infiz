#ifndef INFIZ_STRING_TOKENIZER_H
#define INFIZ_STRING_TOKENIZER_H

#include <string>

// StringTokenizer.h

/**
 * A Class that tokenizes strings consisting of
 * arithmetic operators and numbers.
 */

class StringTokenizer
{
public:
  explicit StringTokenizer(std::string n_string) noexcept;

  auto hasMoreTokens() const noexcept -> bool { return moreTokens; }

  auto nextToken() -> std::string;

private:
  std::string string;
  std::size_t currentOffset;
  bool moreTokens;

};


constexpr auto isOperator(char input) noexcept -> bool
{
  switch (input) {
  case '+':
  case '-':
  case '/':
  case '*':
  case '(':
  case ')':
    return true;
  default:
    return false;
  }
}


constexpr auto isNumber(char input) noexcept -> bool
{
  switch (input) {
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '0':
    return true;
  default:
    return false;
  }
}


constexpr auto isWhiteSpace(char input) noexcept -> bool { return !isNumber(input) && !isOperator(input); }


#endif