#ifndef LIBINFIZ_HPP
#define LIBINFIZ_HPP

#include <infiz/libinfiz_export.hpp>

LIBINFIZ_EXPORT int factorial(int) noexcept;

int factorial_constexpr(int input) noexcept
{
  if (input == 0) { return 1; }

  return input * factorial_constexpr(input - 1);
}

#endif
