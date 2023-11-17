include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(infiz_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(infiz_setup_options)
  option(infiz_ENABLE_HARDENING "Enable hardening" ON)
  option(infiz_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    infiz_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    infiz_ENABLE_HARDENING
    OFF)

  infiz_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR infiz_PACKAGING_MAINTAINER_MODE)
    option(infiz_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(infiz_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(infiz_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(infiz_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(infiz_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(infiz_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(infiz_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(infiz_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(infiz_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(infiz_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(infiz_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(infiz_ENABLE_PCH "Enable precompiled headers" OFF)
    option(infiz_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(infiz_ENABLE_IPO "Enable IPO/LTO" ON)
    option(infiz_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(infiz_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(infiz_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(infiz_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(infiz_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(infiz_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(infiz_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(infiz_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(infiz_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(infiz_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(infiz_ENABLE_PCH "Enable precompiled headers" OFF)
    option(infiz_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      infiz_ENABLE_IPO
      infiz_WARNINGS_AS_ERRORS
      infiz_ENABLE_USER_LINKER
      infiz_ENABLE_SANITIZER_ADDRESS
      infiz_ENABLE_SANITIZER_LEAK
      infiz_ENABLE_SANITIZER_UNDEFINED
      infiz_ENABLE_SANITIZER_THREAD
      infiz_ENABLE_SANITIZER_MEMORY
      infiz_ENABLE_UNITY_BUILD
      infiz_ENABLE_CLANG_TIDY
      infiz_ENABLE_CPPCHECK
      infiz_ENABLE_COVERAGE
      infiz_ENABLE_PCH
      infiz_ENABLE_CACHE)
  endif()

  infiz_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (infiz_ENABLE_SANITIZER_ADDRESS OR infiz_ENABLE_SANITIZER_THREAD OR infiz_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(infiz_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(infiz_global_options)
  if(infiz_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    infiz_enable_ipo()
  endif()

  infiz_supports_sanitizers()

  if(infiz_ENABLE_HARDENING AND infiz_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR infiz_ENABLE_SANITIZER_UNDEFINED
       OR infiz_ENABLE_SANITIZER_ADDRESS
       OR infiz_ENABLE_SANITIZER_THREAD
       OR infiz_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${infiz_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${infiz_ENABLE_SANITIZER_UNDEFINED}")
    infiz_enable_hardening(infiz_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(infiz_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(infiz_warnings INTERFACE)
  add_library(infiz_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  infiz_set_project_warnings(
    infiz_warnings
    ${infiz_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(infiz_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(infiz_options)
  endif()

  include(cmake/Sanitizers.cmake)
  infiz_enable_sanitizers(
    infiz_options
    ${infiz_ENABLE_SANITIZER_ADDRESS}
    ${infiz_ENABLE_SANITIZER_LEAK}
    ${infiz_ENABLE_SANITIZER_UNDEFINED}
    ${infiz_ENABLE_SANITIZER_THREAD}
    ${infiz_ENABLE_SANITIZER_MEMORY})

  set_target_properties(infiz_options PROPERTIES UNITY_BUILD ${infiz_ENABLE_UNITY_BUILD})

  if(infiz_ENABLE_PCH)
    target_precompile_headers(
      infiz_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(infiz_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    infiz_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(infiz_ENABLE_CLANG_TIDY)
    infiz_enable_clang_tidy(infiz_options ${infiz_WARNINGS_AS_ERRORS})
  endif()

  if(infiz_ENABLE_CPPCHECK)
    infiz_enable_cppcheck(${infiz_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(infiz_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    infiz_enable_coverage(infiz_options)
  endif()

  if(infiz_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(infiz_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(infiz_ENABLE_HARDENING AND NOT infiz_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR infiz_ENABLE_SANITIZER_UNDEFINED
       OR infiz_ENABLE_SANITIZER_ADDRESS
       OR infiz_ENABLE_SANITIZER_THREAD
       OR infiz_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    infiz_enable_hardening(infiz_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
