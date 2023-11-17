#ifndef INFIZ_STRING_TOKENIZER_H
#define INFIZ_STRING_TOKENIZER_H


// StringTokenizer.h

/**
 * A Class that tokenizes strings consisting of
 * arithmetic operators and numbers.
 */

class StringTokenizer
{
public:
	StringTokenizer(char * n_string);
	~StringTokenizer();
	
	int hasMoreTokens();

	char * nextToken();


private:
	int currentOffset;
	int stringLen;
	char * string;
	int isNumber(char c);
	int isOperator(char c);
	int isWhiteSpace(char c);
	char * getSubString(char * string, int start, int end);
	int findTokenEnd(int start, char * string);
	int moreTokens;
};

#endif