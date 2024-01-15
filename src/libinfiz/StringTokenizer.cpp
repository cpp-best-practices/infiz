// StringTokenizer.cpp

#include "StringTokenizer.hpp"
#include <string>
#include <utility>

StringTokenizer::StringTokenizer(std::string n_string) noexcept
  : string(std::move(n_string)), currentOffset(0), moreTokens(true)
{}

auto findTokenEnd(std::size_t start, const std::string &string) -> std::size_t
{
  if (string.empty()) { return start; }

  if (isNumber(string[start])) {
    while (start < string.size() && isNumber(string[start])) { ++start; }
  } else if (isOperator(string[start])) {
    ++start;
  }


  return start;
}


auto StringTokenizer::nextToken() -> std::string
{
  while (currentOffset < string.size() && isWhiteSpace(string[currentOffset])) { ++currentOffset; }

  const auto endOfToken = findTokenEnd(currentOffset, string);
  auto returnValue = string.substr(currentOffset, endOfToken - currentOffset) ;
  currentOffset = endOfToken;
  moreTokens = endOfToken < string.size();

  return returnValue;
}

