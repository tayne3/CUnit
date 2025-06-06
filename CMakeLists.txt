cmake_minimum_required(VERSION 3.12)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/GitVersion.cmake)
gitversion_extract(VERSION PROJECT_VERSION DEFAULT_VERSION 0.1.6)
project(CUnit VERSION ${PROJECT_VERSION})

include(cmake/ProjectIsTopLevel.cmake)
include(cmake/OptionVariables.cmake)
include(cmake/ProjectConfig.cmake)

file(GLOB_RECURSE cunit_source_files CONFIGURE_DEPENDS src/*.c)
add_library(cunit ${CUNIT_LIB_TYPE} ${cunit_source_files})
target_include_directories(cunit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(cunit PRIVATE cunit_compile_dependency)

add_library(cunit::cunit ALIAS cunit)
add_library(cunit::${CUNIT_LIB_NAME} ALIAS cunit)
message(STATUS "CUnit ${PROJECT_VERSION} ${CUNIT_LIB_NAME} library")

if(CUNIT_BUILD_EXAMPLE)
    enable_testing()
    add_subdirectory(example)
endif()
