
#include <stdlib.h>
#include "Evaluator.hpp"


#define PLUS_SIGN 0
#define CLOSE_PARAN 1
#define OPEN_PARAN 2
#define MINUS_SIGN 3
#define DIVIDE_SIGN 4
#define MULTIPLY_SIGN 5

#define TRUE 1
#define FALSE 0


int precedence(int op) {
	switch (op) {
	case CLOSE_PARAN:
		return 3;
	case PLUS_SIGN:
		return 1;
	case MINUS_SIGN:
		return 1;
	case MULTIPLY_SIGN:
		return 2;
	case DIVIDE_SIGN:
		return 2;
	case OPEN_PARAN:
		return 0;
	}

	return 0;
}


void evaluateStacks(Stack<RationalNumber> &numbers, Stack<int> &operators, int num) {
	int eatOpenParan = FALSE;
	int cont = TRUE;

	int startPrec = precedence(*operators.peek());

	if ( *operators.peek() == CLOSE_PARAN ) {
		eatOpenParan = TRUE;
		operators.pop();
	}

	while ( (operators.peek() != NULL) && cont) {


		switch( *operators.peek() ) {
		case OPEN_PARAN:
			if (eatOpenParan == TRUE) {
				operators.pop();
				cont = FALSE;
			}

			else
				cont = FALSE;

			break;
			
		case PLUS_SIGN:{
			operators.pop();
			RationalNumber operand2 = numbers.pop();
			RationalNumber operand1 = numbers.pop();

			operand1.add(operand2);
			numbers.push(operand1);
			break;
					   }

		case MINUS_SIGN: {
			operators.pop();
			RationalNumber operand1 = numbers.pop();
			operand1.negate();

			numbers.push(operand1);
			break;
						 }

		case MULTIPLY_SIGN: {
			operators.pop();
			RationalNumber operand2 = numbers.pop();
			RationalNumber operand1 = numbers.pop();

			operand1.multiply(operand2);
			numbers.push(operand1);
			break;
							}

		case DIVIDE_SIGN: {
			operators.pop();
			RationalNumber operand2 = numbers.pop();
			RationalNumber operand1 = numbers.pop();

			operand1.divide(operand2);
			numbers.push(operand1);
			break;
						  }
		}
		
		if (num == 1) 
			cont = FALSE;

	}
}




RationalNumber evaluateExpression(StringTokenizer & st) {
	Stack<int> operators;
	Stack<RationalNumber> numbers;

	int negateNext = FALSE;

	int op;

	while (st.hasMoreTokens()) {

		std::string next = st.nextToken();

		int value = 0;

		if (!next.empty()) {
			switch(next[0]) {
			case '+':
				value = PLUS_SIGN;
				op = TRUE;
				break;
			case '/':
				value = DIVIDE_SIGN;
				op = TRUE;
				break;
			case '-':
				value = MINUS_SIGN;
				op = TRUE;
				break;
			case '*':
				value = MULTIPLY_SIGN;
				op = TRUE;
				break;
			case ')':
				value = CLOSE_PARAN;
				op = TRUE;
				break;
			case '(':
				value = OPEN_PARAN;
				op = TRUE;
				break;

			default:
				value = atoi(next.c_str());
				op = FALSE;
				numbers.push(RationalNumber(value, 1));
				break;
			}

			if (op) {

				int plus = PLUS_SIGN;

				switch (value) {
				case OPEN_PARAN:
					operators.push(value);
					break;
				case CLOSE_PARAN:
					operators.push(value);
					evaluateStacks(numbers, operators, 0);
					break;
				default:
					if (operators.peek() != NULL) {
						if ( precedence(value) >= precedence(*operators.peek()) ) {
							operators.push(value);
						}
						if ( precedence(value) < precedence(*operators.peek()) ) {
							evaluateStacks(numbers, operators, 0);
							operators.push(value);
						}
					}
					else
						operators.push(value);
					break;
				}
			}
		}
	}

	if (operators.peek() != NULL)
		evaluateStacks(numbers, operators, 0);

	if (numbers.peek() != NULL) {
		return *numbers.peek(); 
	} else {
		return RationalNumber(0,0);
	}
}

