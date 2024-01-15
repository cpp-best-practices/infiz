#ifndef INFIZ_STACK_HPP
#define INFIZ_STACK_HPP


#include <cassert>
#include <cstddef>
#include <vector>
#include <stdexcept>


template<typename Contained> class Stack
{
public:
  constexpr Stack() = default;

  [[nodiscard]] constexpr auto empty() const noexcept -> bool { return data.empty(); }

  constexpr auto pop() -> Contained
  {
    if (data.empty()) { throw std::runtime_error("No elements left to pop!"); }
    Contained toReturn = data.back();
    data.pop_back();
    return toReturn;
  }

  template<typename... Param> constexpr auto emplace(Param &&...param) -> Contained &
  {
    return data.emplace_back(std::forward<Param>(param)...);
  }

  constexpr void push(const Contained &newElem) { data.push_back(newElem); }

  [[nodiscard]] constexpr auto peek() const -> const Contained *
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