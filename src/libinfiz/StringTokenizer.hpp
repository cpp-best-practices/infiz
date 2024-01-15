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

  bool hasMoreTokens() const noexcept { return moreTokens; }

  std::string nextToken();

private:
  std::string string;
  std::size_t currentOffset;
  bool moreTokens;

  static bool isNumber(char input) noexcept;
  static bool isOperator(char input) noexcept;
  static bool isWhiteSpace(char input) noexcept;
  static std::size_t findTokenEnd(std::size_t start, const std::string &);
};

#endif