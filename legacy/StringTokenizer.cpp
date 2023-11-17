// StringTokenizer.cpp

#include "StringTokenizer.h"
#include <string.h>

StringTokenizer::StringTokenizer(char * n_string) {

	string = new char[strlen(n_string)];
	strcpy(string, n_string);

	stringLen = strlen(string);

	currentOffset = 0;
	moreTokens = 1;
}

StringTokenizer::~StringTokenizer() 
{
	delete string;
}

char * StringTokenizer::nextToken() 
{
	char* toReturn;
	
	int cont = 1;
	int endOfToken;

	for (;(currentOffset<stringLen) && (isWhiteSpace(string[currentOffset])); currentOffset++);

	endOfToken = findTokenEnd(currentOffset, string);

	toReturn = getSubString(string, currentOffset, endOfToken);

	currentOffset = endOfToken + 1;

	if (currentOffset == stringLen)
		moreTokens = 0;

	return toReturn;
}

int StringTokenizer::hasMoreTokens() {
	return moreTokens;
}

int StringTokenizer::findTokenEnd(int start, char * string) {
	
	if ( isNumber(string[start]) )  {
		for (; (currentOffset<stringLen) && (isNumber(string[start])); start++);
	}

	else {
		if ( isOperator(string[start]) )  {
			start++;
		}
	}

	return start-1;
}



char * StringTokenizer::getSubString(char * string, int start, int end) {
	char * toReturn;
	
	int len = end - start + 1;
	
	toReturn = new char[len+1];
	
	toReturn[len] = NULL;

	for (int i = 0; i<len; i++)
		toReturn[i] = string[i+start];

	return toReturn;
}


int StringTokenizer::isOperator(char c) {
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
	

int StringTokenizer::isNumber(char c) {
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


int StringTokenizer::isWhiteSpace(char c) {
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


