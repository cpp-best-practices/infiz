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
	typedef std::string::size_type size_type;

	explicit StringTokenizer(const std::string &n_string);
	
	bool hasMoreTokens() const;

	std::string nextToken();

private:
	std::string string;
	size_type currentOffset;
	bool moreTokens;

	static bool isNumber(char input);
	static bool isOperator(char input);
	static bool isWhiteSpace(char input);
	static size_type findTokenEnd(size_type start, const std::string &);
};

#endif