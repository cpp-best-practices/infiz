// StringTokenizer.cpp

#include "StringTokenizer.h"
#include <string.h>

StringTokenizer::StringTokenizer(const std::string &n_string)
  : string(n_string), currentOffset(0), moreTokens(true)
{
}


std::string StringTokenizer::nextToken() 
{	
	for (;(currentOffset<string.size()) && (isWhiteSpace(string[currentOffset])); currentOffset++);
	
	int endOfToken = findTokenEnd(currentOffset, string);
	
	std::string toReturn = getSubString(string, currentOffset, endOfToken);
	
	currentOffset = endOfToken + 1;
	
	moreTokens = currentOffset < string.size();
	
	return toReturn;
}

bool StringTokenizer::hasMoreTokens() const {
	return moreTokens;
}

int StringTokenizer::findTokenEnd(int start, const std::string& string) {
	if ( isNumber(string[start]) )  {
		for (; (start<string.size()) && (isNumber(string[start])); ++start) {}
	} else {
		if ( isOperator(string[start]) )  {
			++start;
		}
	}
	
	return start-1;
}



std::string StringTokenizer::getSubString(const std::string &string, int start, int end) {
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
		return 1;
		break;
	default:
		return 0;
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
		return 1;
		break;
	default:
		return 0;
		break;
	}
}


bool StringTokenizer::isWhiteSpace(char c) {
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
	case '+':
	case '-':
	case '/':
	case '*':
	case '(':
	case ')':
		return 0;
		break;
	default:
		return 1;
		break;
	}
}


