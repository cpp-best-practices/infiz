#ifndef INFIZ_EVALUATOR_HPP
#define INFIZ_EVALUATOR_HPP

#include "RationalNumber.h"
#include "Stack.h"
#include "StringTokenizer.h"

int precedence(int op);
RationalNumber evaluateExpression(StringTokenizer &st);
void evaluateStacks(Stack<RationalNumber> &numbers, Stack<int> &operators);

#endif