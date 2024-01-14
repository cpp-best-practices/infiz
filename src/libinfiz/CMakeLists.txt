include(GenerateExportHeader)


add_library(libinfiz
        Evaluator.cpp
        RationalNumber.cpp
        StringTokenizer.cpp)



add_library(infiz::libinfiz ALIAS libinfiz)

target_link_libraries(libinfiz PRIVATE infiz_options infiz_warnings)

target_include_directories(libinfiz ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(libinfiz PUBLIC cxx_std_20)

set_target_properties(
  libinfiz
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(libinfiz EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/infiz/libinfiz_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(libinfiz PUBLIC libinfiz_STATIC_DEFINE)
endif()
