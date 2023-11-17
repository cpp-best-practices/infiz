//infiz.cpp

#include "StringTokenizer.h"
#include "Stack.h"
#include "RationalNumber.h"
#include "Evaluator.hpp"

#include <iostream.h>
#include <stdlib.h>


void main(int argc, char * args[]) {
	
	char input[255];

	cin.getline(input,254, '\n');

	while (cin) {
		StringTokenizer st(input);
		RationalNumber answer = evaluateExpression(st);
		cout << "answer: ";
		if (answer.getDenominator()==1)
			cout <<answer.getNumerator()<<endl<<flush;
		else
			cout <<answer.getNumerator()<<'/'<<answer.getDenominator()<<" ("<<answer.getFloat()<<")"<< '\n';
		cin.getline(input,254, '\n');
	}
}

