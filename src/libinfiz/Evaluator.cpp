
#include "Evaluator.hpp"
#include <cstdlib>


int precedence(Operators input)
{
  switch (input) {
  case CLOSE_PAREN:
    return 3;
  case PLUS_SIGN:
  case MINUS_SIGN:
    return 1;
  case MULTIPLY_SIGN:
  case DIVIDE_SIGN:
    return 2;
  case OPEN_PAREN:
    return 0;
  }

  return 0;
}


void evaluateStacks(Stack<RationalNumber> &numbers, Stack<int> &operators)
{
  bool eatOpenParen = false;
  bool cont = true;

  if (*operators.peek() == CLOSE_PAREN) {
    eatOpenParen = true;
    operators.pop();
  }

  while ((operators.peek() != NULL) && cont) {// NOLINT

    switch (*operators.peek()) {
    case OPEN_PAREN:
      if (eatOpenParen) {
        operators.pop();
        cont = false;
      } else {
        cont = false;
      }

      break;

    case PLUS_SIGN: {
      operators.pop();
      const RationalNumber operand2 = numbers.pop();
      const RationalNumber operand1 = numbers.pop();
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
      const RationalNumber operand2 = numbers.pop();
      const RationalNumber operand1 = numbers.pop();
      numbers.push(operand1 * operand2);
      break;
    }

    case DIVIDE_SIGN: {
      operators.pop();
      const RationalNumber operand2 = numbers.pop();
      const RationalNumber operand1 = numbers.pop();
      numbers.push(operand1 / operand2);
      break;
    }
    }
  }
}


RationalNumber evaluateExpression(StringTokenizer &tokenizer)
{
  Stack<int> operators;
  Stack<RationalNumber> numbers;

  while (tokenizer.hasMoreTokens()) {

    std::string next = tokenizer.nextToken();

    Operators value = PLUS_SIGN;

    if (!next.empty()) {
      bool operation = false;
      switch (next[0]) {
      case '+':
        value = PLUS_SIGN;
        operation = true;
        break;
      case '/':
        value = DIVIDE_SIGN;
        operation = true;
        break;
      case '-':
        value = MINUS_SIGN;
        operation = true;
        break;
      case '*':
        value = MULTIPLY_SIGN;
        operation = true;
        break;
      case ')':
        value = CLOSE_PAREN;
        operation = true;
        break;
      case '(':
        value = OPEN_PAREN;
        operation = true;
        break;

      default:
        operation = false;
        numbers.push(RationalNumber(atoi(next.c_str()), 1));// NOLINT
        break;
      }

      if (operation) {
        switch (value) {
        case OPEN_PAREN:
          operators.push(value);
          break;
        case CLOSE_PAREN:
          operators.push(value);
          evaluateStacks(numbers, operators);
          break;
        default:
          if (operators.peek() != NULL// NOLINT
              && precedence(value) <= precedence(static_cast<Operators>(*operators.peek()))) {
            evaluateStacks(numbers, operators);
          }
          operators.push(value);
          break;
        }
      }
    }
  }

  if (operators.peek() != NULL)// NOLINT
    evaluateStacks(numbers, operators);

  if (numbers.peek() != NULL) {// NOLINT
    return *numbers.peek();
  } else {
    return RationalNumber(0, 0);// NOLINT
  }
}
