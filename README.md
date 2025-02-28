# CUnit

CUnit 是一个轻量且易于集成的 C 语言单元测试库，旨在为 C 开发者提供简单而强大的测试框架。它支持多种数据类型的断言，适合嵌入式系统和资源受限的环境。

## ✨ 特性

- **轻量级**：使用 ANSI C (C99) 标准编写，适合嵌入式系统和资源受限的环境。
- **易用性**：提供简单易用的接口，支持多种数据类型的断言。
- **灵活性**：支持静态和动态库的构建，方便集成到现有项目中。
- **丰富的断言**：提供多种断言方法，支持布尔、整数、浮点数、字符串等类型的比较。

## ⌛️ 构建

CUnit 使用 CMake 作为构建系统，支持跨平台编译。

```sh
git clone https://github.com/tayne3/cunit.git && cd cunit
mkdir build && cd build
cmake ..
make
```

## 📦 项目集成

- **使用 FetchContent 集成**:

如果你的项目使用 CMake 作为构建系统，您可以使用 `FetchContent` 将 CUnit 作为依赖集成到您的项目中：

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(MyLibrary)
add_library(mylib SHARED mylib.c)

include(FetchContent)
FetchContent_Declare(
  CUnit
  GIT_REPOSITORY https://github.com/tayne3/cunit.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(CUnit)

enable_testing()
add_executable(MyTest main_test.c)
target_link_libraries(MyTest mylib cunit::cunit)
add_test(NAME MyTest COMMAND MyTest)
set_tests_properties(MyTest PROPERTIES FAIL_REGULAR_EXPRESSION "failed|error")
```

- **使用 CPM 依赖管理**:

CPM 是一个 CMake 的依赖管理工具，您可以使用 CPM 将 CUnit 作为依赖集成到您的项目中：

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(MyLibrary)
add_library(mylib SHARED mylib.c)

include(cmake/CPM.cmake)
CPMAddPackage("https://github.com/tayne3/cunit.git#1.0.0")

enable_testing()
add_executable(MyTest main_test.c)
target_link_libraries(MyTest mylib cunit::cunit)
add_test(NAME MyTest COMMAND MyTest)
set_tests_properties(MyTest PROPERTIES FAIL_REGULAR_EXPRESSION "failed|error")
```
