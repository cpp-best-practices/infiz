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

  [[nodiscard]] auto empty() const noexcept -> bool { return data.empty(); }

  auto pop() -> Contained
  {
    // TODO is an assert the best option here?
    assert(!data.empty());
    Contained toReturn = data.back();
    data.pop_back();
    return toReturn;
  }

  template<typename... Param> auto emplace(Param &&...param) -> Contained &
  {
    data.emplace_back(std::forward<Param>(param)...);
    return data.back();
  }

  void push(const Contained &newElem) { data.push_back(newElem); }

  [[nodiscard]] auto peek() const -> const Contained *
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