include(GenerateExportHeader)


add_library(libinfiz INTERFACE)



add_library(infiz::libinfiz ALIAS libinfiz)


target_include_directories(libinfiz ${WARNING_GUARD} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)


set_target_properties(
  libinfiz
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(libinfiz EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/infiz/libinfiz_export.hpp)

