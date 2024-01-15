#ifndef INFIZ_STACK_HPP
#define INFIZ_STACK_HPP

// Stack.h

#include <cassert>
#include <cstddef>
#include <vector>

/**
 * A Class that allows allows void * to be
 * pushed onto an popped off of a stack.
 */

template<typename Contained> class Stack
{
public:
  Stack() = default;

  bool empty() const noexcept {
    return data.empty();
  }

  Contained pop()
  {
    assert(!data.empty());
    Contained toReturn = data.back();
    data.pop_back();
    return toReturn;
  }

  template<typename ... Param>
  Contained &emplace( Param && ... param) {
    data.emplace_back(std::forward<Param>(param)...);
    return data.back();
  }

  void push(const Contained &newElem) { data.push_back(newElem); }

  const Contained *peek() const
  {
    if (data.empty()) {
      return nullptr;
    } else {
      return &data.back();
    }
  }

private:
  std::vector<Contained> data;
};

#endif