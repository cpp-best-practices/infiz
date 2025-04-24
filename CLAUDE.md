# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands
- Configure: `cmake -S . -B ./build -G Ninja` or `cmake . --preset <configure-preset>` (CMake 3.21+)
- Build: `cmake --build ./build`
- Run tests: `cd ./build && ctest -C Debug && cd ..`
- Run specific test: `cd ./build && ./test/tests "[test name]" && cd ..`
- Static analysis: Enable with `-Dinfiz_ENABLE_CLANG_TIDY=ON` or `-Dinfiz_ENABLE_CPPCHECK=ON`

## Code Style Guidelines
- Standard: C++23
- Formatting: 2-space indentation, 120 char line limit, braces on new lines for functions/classes
- Naming: Classes=PascalCase, Methods/Variables=camelCase, Constants/Enums=UPPER_CASE
- Error handling: Use exceptions with descriptive messages, lambda error handlers
- Features: Use `constexpr`, `consteval`, `[[nodiscard]]`, concepts, format strings
- Headers: Include guards with `INFIZ_NAME_H` format, sort includes logically
- Functions: Prefer pure functions marked with `[[nodiscard]]` where possible