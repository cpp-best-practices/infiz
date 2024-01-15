// StringTokenizer.cpp

#include "StringTokenizer.hpp"
#include <string>
#include <utility>

StringTokenizer::StringTokenizer(std::string n_string) noexcept
  : string(std::move(n_string)), currentOffset(0), moreTokens(true)
{}


std::string StringTokenizer::nextToken()
{
  while (currentOffset < string.size() && isWhiteSpace(string[currentOffset])) { ++currentOffset; }

  const auto endOfToken = findTokenEnd(currentOffset, string);

  std::string toReturn = string.substr(currentOffset, endOfToken - currentOffset);
  currentOffset = endOfToken;

  moreTokens = currentOffset < string.size();

  return toReturn;
}


std::size_t StringTokenizer::findTokenEnd(std::size_t start, const std::string &string)
{
  if (string.empty()) { return start; }

  if (isNumber(string[start])) {
    while (start < string.size() && isNumber(string[start])) { ++start; }
  } else if (isOperator(string[start])) {
    ++start;
  }


  return start;
}


bool StringTokenizer::isOperator(char input) noexcept
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


bool StringTokenizer::isNumber(char input) noexcept
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


bool StringTokenizer::isWhiteSpace(char input) noexcept { return !isNumber(input) && !isOperator(input); }
