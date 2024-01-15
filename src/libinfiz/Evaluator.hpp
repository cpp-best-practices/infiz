#ifndef INFIZ_EVALUATOR_HPP
#define INFIZ_EVALUATOR_HPP

#include "RationalNumber.hpp"
#include "Stack.hpp"
#include "StringTokenizer.hpp"

enum struct Operators { PLUS_SIGN, CLOSE_PAREN, OPEN_PAREN, MINUS_SIGN, DIVIDE_SIGN, MULTIPLY_SIGN };


RationalNumber evaluateExpression(StringTokenizer &tokenizer);
void evaluateStacks(Stack<RationalNumber> &numbers, Stack<Operators> &operators);

#endif