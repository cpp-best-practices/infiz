
#include "Evaluator.hpp"
#include <cstdlib>


int precedence(Operators input) noexcept
{
  switch (input) {
  case Operators::CLOSE_PAREN:
    return 3;
  case Operators::PLUS_SIGN:
  case Operators::MINUS_SIGN:
    return 1;
  case Operators::MULTIPLY_SIGN:
  case Operators::DIVIDE_SIGN:
    return 2;
  case Operators::OPEN_PAREN:
    return 0;
  }

  return 0;
}


void evaluateStacks(Stack<RationalNumber> &numbers, Stack<Operators> &operators)
{
  bool eatOpenParen = false;
  bool cont = true;

  if (!operators.empty() && *operators.peek() == Operators::CLOSE_PAREN) {
    eatOpenParen = true;
    operators.pop();
  }

  while (!operators.empty() && cont && (operators.peek() != nullptr)) {

    switch (*operators.peek()) {
    case Operators::OPEN_PAREN:
      if (eatOpenParen) {
        operators.pop();
        cont = false;
      } else {
        cont = false;
      }

      break;

    case Operators::PLUS_SIGN: {
      operators.pop();
      const auto operand2 = numbers.pop();
      const auto operand1 = numbers.pop();
      numbers.push(operand1 + operand2);
      break;
    }

    case Operators::MINUS_SIGN: {
      operators.pop();
      numbers.push(-numbers.pop());
      break;
    }

    case Operators::MULTIPLY_SIGN: {
      operators.pop();
      const auto operand2 = numbers.pop();
      const auto operand1 = numbers.pop();
      numbers.push(operand1 * operand2);
      break;
    }

    case Operators::DIVIDE_SIGN: {
      operators.pop();
      const auto operand2 = numbers.pop();
      const auto operand1 = numbers.pop();
      numbers.push(operand1 / operand2);
      break;
    }

    case Operators::CLOSE_PAREN:
      break;// we want to continue
    }
  }
}


RationalNumber evaluateExpression(StringTokenizer &tokenizer)
{
  Stack<Operators> operators;
  Stack<RationalNumber> numbers;

  while (tokenizer.hasMoreTokens()) {

    auto next = tokenizer.nextToken();

    auto value = Operators::PLUS_SIGN;

    if (!next.empty()) {
      auto operation = false;
      switch (next[0]) {
      case '+':
        value = Operators::PLUS_SIGN;
        operation = true;
        break;
      case '/':
        value = Operators::DIVIDE_SIGN;
        operation = true;
        break;
      case '-':
        value = Operators::MINUS_SIGN;
        operation = true;
        break;
      case '*':
        value = Operators::MULTIPLY_SIGN;
        operation = true;
        break;
      case ')':
        value = Operators::CLOSE_PAREN;
        operation = true;
        break;
      case '(':
        value = Operators::OPEN_PAREN;
        operation = true;
        break;

      default:
        operation = false;
        numbers.emplace(atoi(next.c_str()), 1);// NOLINT
        break;
      }

      if (operation) {
        switch (value) {
        case Operators::OPEN_PAREN:
          operators.push(value);
          break;
        case Operators::CLOSE_PAREN:
          operators.push(value);
          evaluateStacks(numbers, operators);
          break;
        default:
          if (operators.peek() != nullptr && precedence(value) <= precedence(*operators.peek())) {
            evaluateStacks(numbers, operators);
          }
          operators.push(value);
          break;
        }
      }
    }
  }

  if (operators.peek() != nullptr) { evaluateStacks(numbers, operators); }

  if (numbers.peek() != nullptr) {
    return *numbers.peek();
  } else {
    return { 0, 0 };
  }
}
