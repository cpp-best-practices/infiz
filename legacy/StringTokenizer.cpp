// StringTokenizer.cpp

#include "StringTokenizer.h"
#include <string.h>

StringTokenizer::StringTokenizer(const std::string &n_string)
  : string(n_string), currentOffset(0), moreTokens(true)
{
}


std::string StringTokenizer::nextToken() 
{	
	while (currentOffset<string.size() 
		&& isWhiteSpace(string[currentOffset])) {
		++currentOffset;
	}
	
	size_type endOfToken = findTokenEnd(currentOffset, string);
	
	std::string toReturn = string.substr(currentOffset, endOfToken-currentOffset);
	currentOffset = endOfToken;
	
	moreTokens = currentOffset < string.size();
	
	return toReturn;
}

bool StringTokenizer::hasMoreTokens() const {
	return moreTokens;
}

StringTokenizer::size_type StringTokenizer::findTokenEnd(size_type start, const std::string& string) {
	if (string.empty()) {
		return start;
	}

	if (isNumber(string[start])) {
		while (start < string.size() && isNumber(string[start])) {
			++start;
		}
	} else if ( isOperator(string[start]) )  {
		++start;
	}
	
	
	return start;
}



std::string StringTokenizer::getSubString(const std::string &string, size_type start, size_type end) {
	return string.substr(start, end);
}


bool StringTokenizer::isOperator(char c) {
	switch (c) {
	case '+':
	case '-':
	case '/':
	case '*':
	case '(':
	case ')':
		return true;
		break;
	default:
		return false;
		break;
	}
}


bool StringTokenizer::isNumber(char c) {
	switch (c) {
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
		break;
	default:
		return false;
		break;
	}
}


bool StringTokenizer::isWhiteSpace(char c) {
	return !isNumber(c) && !isOperator(c);
}


