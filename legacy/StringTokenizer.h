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
	StringTokenizer(const std::string &n_string);
	
	bool hasMoreTokens() const;

	std::string nextToken();

private:
	std::string string;
	int currentOffset;
	bool moreTokens;

	static bool isNumber(char c);
	static bool isOperator(char c);
	static bool isWhiteSpace(char c);
	static std::string getSubString(const std::string &, int start, int end);
	static int findTokenEnd(int start, const std::string &);
};

#endif