#ifndef INFIZ_STRING_TOKENIZER_H
#define INFIZ_STRING_TOKENIZER_H

#include <string_view>



[[nodiscard]] constexpr auto isOperator(char input) noexcept -> bool
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


[[nodiscard]] constexpr auto isNumber(char input) noexcept -> bool
{
  switch (input) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return true;
  default:
    return false;
  }
}

[[nodiscard]] constexpr auto findTokenEnd(std::size_t start, std::string_view string) -> std::size_t
{
  if (string.size() <= start) { return start; }

  if (isNumber(string[start])) {
    while (start < string.size() && isNumber(string[start])) { ++start; }
  } else if (isOperator(string[start])) {
    ++start;
  }


  return start;
}


[[nodiscard]] constexpr auto isWhiteSpace(char input) noexcept -> bool
{
  return !isNumber(input) && !isOperator(input);
}


/**
 * A Class that tokenizes strings consisting of
 * arithmetic operators and numbers.
 */
class StringTokenizer
{
public:
  constexpr explicit StringTokenizer(std::string_view n_string) noexcept
    : string(n_string)
  {}


  [[nodiscard]] constexpr auto nextToken() -> std::string_view
  {
    while (currentOffset < string.size() && isWhiteSpace(string[currentOffset])) { ++currentOffset; }

    const auto endOfToken = findTokenEnd(currentOffset, string);
    auto returnValue = string.substr(currentOffset, endOfToken - currentOffset);
    currentOffset = endOfToken;
    moreTokens = endOfToken < string.size();

    return returnValue;
  }

  [[nodiscard]] constexpr auto hasMoreTokens() const {
    return moreTokens;
  }

private:
  std::string_view string;
  std::size_t currentOffset{0};
  bool moreTokens{true};

};


#endif