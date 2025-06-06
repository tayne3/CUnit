add_library(cunit_compile_dependency INTERFACE)
target_compile_features(cunit_compile_dependency INTERFACE c_std_99)

string(TOLOWER "${CMAKE_SYSTEM_NAME}" SYSTEM_NAME)
if(CUNIT_BUILD_DEBUG)
	set(CUNIT_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/bin/debug-${SYSTEM_NAME})
	target_compile_definitions(cunit_compile_dependency INTERFACE -DDEBUG)
else()
	set(CUNIT_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/bin/release-${SYSTEM_NAME})
	target_compile_definitions(cunit_compile_dependency INTERFACE -DNDEBUG)
endif()

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CUNIT_OUTPUT_DIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CUNIT_OUTPUT_DIR})
endif()
# if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
# 	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CUNIT_OUTPUT_DIR})
# endif()

include(GNUInstallDirs)
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH OFF)
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_INSTALL_RPATH "@loader_path;@loader_path/${CMAKE_INSTALL_LIBDIR}")
else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/${CMAKE_INSTALL_LIBDIR}")
endif()

if(PROJECT_IS_TOP_LEVEL)
	find_program(CCACHE_PROGRAM ccache)
	if(CCACHE_PROGRAM)
		set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
		set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
	endif()
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set specific C language options for the MSVC compiler
if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(cunit_compile_dependency INTERFACE 
		"$<$<COMPILE_LANGUAGE:C>:/source-charset:utf-8>"
	)
endif()

# Set C language warning options for compilers other than MSVC and ClangCL (MSVC frontend).
# These options help catch potential code issues.
if(NOT (CMAKE_C_COMPILER_ID STREQUAL "MSVC" OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_C_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")))
    target_compile_options(cunit_compile_dependency INTERFACE
        "$<$<COMPILE_LANGUAGE:C>:-Wall>"
        "$<$<COMPILE_LANGUAGE:C>:-Wextra>"
        "$<$<COMPILE_LANGUAGE:C>:-Werror=return-type>"
    )
endif()

# Handle specific warning suppression options for older GCC versions (less than 6.0).
# -Wno-missing-field-initializers is used to suppress warnings about incompletely initialized structs.
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_C_COMPILER_VERSION VERSION_LESS 6.0)
    target_compile_options(cunit_compile_dependency INTERFACE 
		"$<$<COMPILE_LANGUAGE:C>:-Wno-missing-field-initializers>"
	)
endif()

# Set the CUNIT_ROOT_PATH and CUNIT_BUILD_PATH variables.
if(CMAKE_C_COMPILER_ID STREQUAL "MSVC" OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_C_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC"))
    string(REPLACE "/" "\\\\" CUNIT_ROOT_PATH ${CMAKE_SOURCE_DIR})
    string(REPLACE "/" "\\\\" CUNIT_BUILD_PATH ${CMAKE_BINARY_DIR})
else()
    set(CUNIT_ROOT_PATH ${CMAKE_SOURCE_DIR})
    set(CUNIT_BUILD_PATH ${CMAKE_BINARY_DIR})
endif()
target_compile_definitions(cunit_compile_dependency INTERFACE
    CUNIT_ROOT_PATH="${CUNIT_ROOT_PATH}"
    CUNIT_BUILD_PATH="${CUNIT_BUILD_PATH}"
)
