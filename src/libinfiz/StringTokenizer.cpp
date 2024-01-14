// StringTokenizer.cpp

#include "StringTokenizer.h"
#include <string>

StringTokenizer::StringTokenizer(const std::string &n_string)// NOLINT
  : string(n_string), currentOffset(0), moreTokens(true)
{}


std::string StringTokenizer::nextToken()
{
  while (currentOffset < string.size() && isWhiteSpace(string[currentOffset])) { ++currentOffset; }

  const size_type endOfToken = findTokenEnd(currentOffset, string);

  std::string toReturn = string.substr(currentOffset, endOfToken - currentOffset);
  currentOffset = endOfToken;

  moreTokens = currentOffset < string.size();

  return toReturn;
}

bool StringTokenizer::hasMoreTokens() const { return moreTokens; }

StringTokenizer::size_type StringTokenizer::findTokenEnd(size_type start, const std::string &string)
{
  if (string.empty()) { return start; }

  if (isNumber(string[start])) {
    while (start < string.size() && isNumber(string[start])) { ++start; }
  } else if (isOperator(string[start])) {
    ++start;
  }


  return start;
}


bool StringTokenizer::isOperator(char input)
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


bool StringTokenizer::isNumber(char input)
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


bool StringTokenizer::isWhiteSpace(char input) { return !isNumber(input) && !isOperator(input); }
