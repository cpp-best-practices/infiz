
#include <stdlib.h>
#include "Evaluator.hpp"

enum Operators{ 
	PLUS_SIGN,
	CLOSE_PAREN,
	OPEN_PAREN,
	MINUS_SIGN,
	DIVIDE_SIGN,
	MULTIPLY_SIGN
};

int precedence(int op) {
	switch (op) {
	case CLOSE_PAREN:
		return 3;
	case PLUS_SIGN:
		return 1;
	case MINUS_SIGN:
		return 1;
	case MULTIPLY_SIGN:
		return 2;
	case DIVIDE_SIGN:
		return 2;
	case OPEN_PAREN:
		return 0;
	}

	return 0;
}


void evaluateStacks(Stack<RationalNumber> &numbers, Stack<int> &operators) {
	bool eatOpenParen = false;
	bool cont = true;

	int startPrec = precedence(*operators.peek());

	if ( *operators.peek() == CLOSE_PAREN ) {
		eatOpenParen = true;
		operators.pop();
	}

	while ( (operators.peek() != NULL) && cont) {

		switch( *operators.peek() ) {
		case OPEN_PAREN:
			if (eatOpenParen == true) {
				operators.pop();
				cont = false;
			} else {
				cont = false;
			}

			break;
			
		case PLUS_SIGN:{
			operators.pop();
			RationalNumber operand2 = numbers.pop();
			RationalNumber operand1 = numbers.pop();
			numbers.push(operand1 + operand2);
			break;
					   }

		case MINUS_SIGN: {
			operators.pop();
			numbers.push(-numbers.pop());
			break;
						 }

		case MULTIPLY_SIGN: {
			operators.pop();
			RationalNumber operand2 = numbers.pop();
			RationalNumber operand1 = numbers.pop();
			numbers.push(operand1 * operand2);
			break;
							}

		case DIVIDE_SIGN: {
			operators.pop();
			RationalNumber operand2 = numbers.pop();
			RationalNumber operand1 = numbers.pop();
			numbers.push(operand1 / operand2);
			break;
						  }
		}
		
	}
}




RationalNumber evaluateExpression(StringTokenizer & st) {
	Stack<int> operators;
	Stack<RationalNumber> numbers;

	bool negateNext = false;


	while (st.hasMoreTokens()) {

		std::string next = st.nextToken();

		Operators value = PLUS_SIGN;
		bool op = false;

		if (!next.empty()) {
			switch(next[0]) {
			case '+':
				value = PLUS_SIGN;
				op = true;
				break;
			case '/':
				value = DIVIDE_SIGN;
				op = true;
				break;
			case '-':
				value = MINUS_SIGN;
				op = true;
				break;
			case '*':
				value = MULTIPLY_SIGN;
				op = true;
				break;
			case ')':
				value = CLOSE_PAREN;
				op = true;
				break;
			case '(':
				value = OPEN_PAREN;
				op = true;
				break;

			default:
				op = false;
				numbers.push(RationalNumber(atoi(next.c_str()), 1));
				break;
			}

			if (op) {
				int plus = PLUS_SIGN;

				switch (value) {
				case OPEN_PAREN:
					operators.push(value);
					break;
				case CLOSE_PAREN:
					operators.push(value);
					evaluateStacks(numbers, operators);
					break;
				default:
					if (operators.peek() != NULL
						&& precedence(value) <= precedence(*operators.peek()) ) {
						evaluateStacks(numbers, operators);
					}
					operators.push(value);
					break;
				}
			}
		}
	}

	if (operators.peek() != NULL)
		evaluateStacks(numbers, operators);

	if (numbers.peek() != NULL) {
		return *numbers.peek(); 
	} else {
		return RationalNumber(0,0);
	}
}

