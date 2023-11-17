
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


void evaluateStacks(Stack * numbers, Stack * operators, int num) {
	int eatOpenParan = FALSE;
	int cont = TRUE;
	RationalNumber * operand1;
	RationalNumber * operand2;

	int startPrec = precedence(*(int *)(operators->peek()));

	if ( *(int *)(operators->peek()) == CLOSE_PARAN ) {
		eatOpenParan = TRUE;
		delete operators->pop();
	}



	while ( (operators->peek() != NULL) && cont) {


		switch( *(int *)(operators->peek()) ) {
		case OPEN_PARAN:
			if (eatOpenParan == TRUE) {
				delete operators->pop();
				cont = FALSE;
			}

			else
				cont = FALSE;

			break;
			
		case PLUS_SIGN:
			delete operators->pop();
			operand2 = (RationalNumber *)numbers->pop();
			operand1 = (RationalNumber *)numbers->pop();

			operand1->add(operand2);
			delete operand2;
			numbers->push(operand1);
			break;

		case MINUS_SIGN:
			delete operators->pop();
			operand1 = (RationalNumber *)numbers->pop();
			operand1->negate();

			numbers->push(operand1);
			break;

		case MULTIPLY_SIGN:
			delete operators->pop();
			operand2 = (RationalNumber *)numbers->pop();
			operand1 = (RationalNumber *)numbers->pop();

			operand1->multiply(operand2);
			delete operand2;
			numbers->push(operand1);
			break;

		case DIVIDE_SIGN:
			delete operators->pop();
			operand2 = (RationalNumber *)numbers->pop();
			operand1 = (RationalNumber *)numbers->pop();

			operand1->divide(operand2);
			delete operand2;
			numbers->push(operand1);
			break;
		}
		
		if (num == 1) 
			cont = FALSE;

	}
}




RationalNumber * evaluateExpression(StringTokenizer * st) {
	Stack * operators = new Stack();
	Stack * numbers = new Stack();

	int negateNext = FALSE;

	int op;

	char * next;

	while (st->hasMoreTokens()) {

		next = st->nextToken();

		int * value = new int;

		if (next != NULL) {
			switch(next[0]) {
			case '+':
				*value = PLUS_SIGN;
				op = TRUE;
				break;
			case '/':
				*value = DIVIDE_SIGN;
				op = TRUE;
				break;
			case '-':
				*value = MINUS_SIGN;
				op = TRUE;
				break;
			case '*':
				*value = MULTIPLY_SIGN;
				op = TRUE;
				break;
			case ')':
				*value = CLOSE_PARAN;
				op = TRUE;
				break;
			case '(':
				*value = OPEN_PARAN;
				op = TRUE;
				break;

			default:
				*value = atoi(next);
				op = FALSE;
				numbers->push(new RationalNumber(*value, 1));
				break;
			}

			if (op) {

				int *plus = new int;
				*plus = PLUS_SIGN;

				switch (*value) {
				case OPEN_PARAN:
					operators->push(value);
					break;
				case CLOSE_PARAN:
					operators->push(value);
					evaluateStacks(numbers, operators, 0);
					break;
				default:
					if (operators->peek() != NULL) {
						if ( precedence(*value) >= precedence(*(int *)(operators->peek())) ) {
							operators->push(value);
						}
						if ( precedence(*value) < precedence(*(int *)(operators->peek())) ) {
							evaluateStacks(numbers, operators, 0);
							operators->push(value);
						}
					}
					else
						operators->push(value);
					break;
				}
			}
		}
	}

	if (operators->peek() != NULL)
		evaluateStacks(numbers, operators, 0);
	return (RationalNumber *)numbers->peek();
}

