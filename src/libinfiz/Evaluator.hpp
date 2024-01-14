#ifndef INFIZ_EVALUATOR_HPP
#define INFIZ_EVALUATOR_HPP

#include "RationalNumber.h"
#include "Stack.h"
#include "StringTokenizer.h"

enum Operators { PLUS_SIGN, CLOSE_PAREN, OPEN_PAREN, MINUS_SIGN, DIVIDE_SIGN, MULTIPLY_SIGN };


int precedence(Operators input);
RationalNumber evaluateExpression(StringTokenizer &tokenizer);
void evaluateStacks(Stack<RationalNumber> &numbers, Stack<int> &operators);

#endif