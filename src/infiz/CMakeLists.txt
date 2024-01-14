add_executable(infiz infiz.cpp)

target_link_libraries(
  infiz
  PUBLIC libinfiz
  PRIVATE infiz::infiz_options
          infiz::infiz_warnings)


target_include_directories(infiz PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
