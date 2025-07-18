cmake_minimum_required(VERSION 3.12)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/GitVersion.cmake)
gitversion_extract(VERSION PROJECT_VERSION DEFAULT_VERSION 0.1.6)
project(cunit VERSION ${PROJECT_VERSION})

include(cmake/ProjectIsTopLevel.cmake)
include(cmake/OptionVariables.cmake)
include(cmake/ProjectConfig.cmake)

file(GLOB_RECURSE project_source_files CONFIGURE_DEPENDS src/*.c)
add_library(${PROJECT_NAME} ${PROJECT_LIB_TYPE} ${project_source_files})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_compile_dependency)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_LIB_NAME} ALIAS ${PROJECT_NAME})

if(CUNIT_BUILD_EXAMPLE)
    enable_testing()
    add_subdirectory(example)
endif()
