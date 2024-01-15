
#include "../src/libinfiz/Evaluator.hpp"
#include <cstdint>

// Fuzzer that attempts to invoke undefined behavior for signed integer overflow
// cppcheck-suppress unusedFunction symbolName=LLVMFuzzerTestOneInput
extern "C" auto LLVMFuzzerTestOneInput(const std::uint8_t *Data, std::size_t Size) -> int
{
  [[maybe_unused]] const auto result = evaluate(std::string_view(reinterpret_cast<const char *>(Data), Size));// NOLINT
  return 0;
}
