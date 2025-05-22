cmake_minimum_required(VERSION 3.14)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/GitVersion.cmake)
gitversion_extract(VERSION PROJECT_VERSION DEFAULT_VERSION 0.1.1)
project(CUnit VERSION ${PROJECT_VERSION})

include(cmake/ProjectIsTopLevel.cmake)
include(cmake/OptionVariables.cmake)
include(cmake/ProjectConfig.cmake)

file(GLOB_RECURSE cunit_source_files CONFIGURE_DEPENDS src/*.c src/*.cpp src/*.cc src/*.h src/*.hpp)
add_library(cunit ${CUNIT_LIB_TYPE} ${cunit_source_files})
target_include_directories(cunit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(cunit PRIVATE ${CUNIT_COMPILE_DEFINITIONS})
target_compile_features(cunit PRIVATE c_std_99 cxx_std_11)
set_target_properties(cunit PROPERTIES OUTPUT_NAME cunit)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
	set(IS_CLANG_CL 1)
else()
	set(IS_CLANG_CL 0)
endif()
if(MSVC OR IS_CLANG_CL)
    string(REPLACE "/" "\\\\" CUNIT_ROOT_PATH ${CMAKE_SOURCE_DIR})
    string(REPLACE "/" "\\\\" CUNIT_BUILD_PATH ${CMAKE_BINARY_DIR})
else()
    set(CUNIT_ROOT_PATH ${CMAKE_SOURCE_DIR})
    set(CUNIT_BUILD_PATH ${CMAKE_BINARY_DIR})
endif()
target_compile_definitions(cunit_obj PRIVATE
    CUNIT_ROOT_PATH="${CUNIT_ROOT_PATH}"
    CUNIT_BUILD_PATH="${CUNIT_BUILD_PATH}"
)

add_library(cunit::cunit ALIAS cunit)
add_library(cunit::${CUNIT_LIB_NAME} ALIAS cunit)
message(STATUS "CUnit ${PROJECT_VERSION} ${CUNIT_LIB_NAME} library")

if(CUNIT_BUILD_EXAMPLE)
    enable_testing()
    add_subdirectory(example)
endif()
