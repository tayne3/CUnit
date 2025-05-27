# 🧪 CUnit: A lightweight and easy-to-integrate C unit testing library

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.12%2B-brightgreen)

CUnit 是一个轻量且易于集成的 C 语言单元测试库，旨在为 C 开发者提供简单而强大的测试框架。它支持多种数据类型的断言，适合嵌入式系统和资源受限的环境。

## ✨ 特性

- **轻量级**：使用 ANSI C (C99) 标准编写，适合嵌入式系统和资源受限的环境。
- **易用性**：提供简单易用的接口，支持多种数据类型的断言。
- **灵活性**：支持静态和动态库的构建，方便集成到现有项目中。
- **丰富的断言**：提供多种断言方法，支持布尔、整数、浮点数、字符串等类型的比较。

## 🛠️ 构建

CUnit 使用 CMake 作为构建系统，支持跨平台编译。

**源码拉取**:

```sh
git clone https://github.com/tayne3/cunit.git
```

**构建**:

```sh
mkdir build
cd build
cmake ..
make
```

## 🔗 项目集成

- **使用 FetchContent 集成**:

如果你的项目使用 CMake 作为构建系统，您可以使用 `FetchContent` 将 CUnit 作为依赖集成到您的项目中：

```cmake
cmake_minimum_required(VERSION 3.12)

project(MyLibrary)
add_library(mylib SHARED mylib.c)

include(FetchContent)
FetchContent_Declare(
  CUnit
  GIT_REPOSITORY https://github.com/tayne3/CUnit.git
  GIT_TAG v0.1.4
)
FetchContent_MakeAvailable(CUnit)

enable_testing()
add_executable(MyTest main_test.c)
target_link_libraries(MyTest mylib cunit::cunit)
add_test(NAME MyTest COMMAND MyTest)
set_tests_properties(MyTest PROPERTIES FAIL_REGULAR_EXPRESSION "failed")
```

- **使用 CPM.cmake 集成**:

> CPM.cmake is a cross-platform CMake script that adds dependency management capabilities to CMake. It's built as a thin wrapper around CMake's FetchContent module that adds version control, caching, a simple API and more.

> To use CPM.cmake, download the `CPM.cmake` file from [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake/releases/latest), place it in your project, and then include it in your main `CMakeLists.txt` file with `include(cmake/CPM.cmake)`.

使用 CPM.cmake 将 CUnit 作为依赖集成到您的项目中：

```cmake
cmake_minimum_required(VERSION 3.12)

project(MyLibrary)
add_library(mylib SHARED mylib.c)

include(cmake/CPM.cmake)
CPMAddPackage("gh:tayne3/CUnit@0.1.4")

enable_testing()
add_executable(MyTest main_test.c)
target_link_libraries(MyTest mylib cunit::cunit)
add_test(NAME MyTest COMMAND MyTest)
set_tests_properties(MyTest PROPERTIES FAIL_REGULAR_EXPRESSION "failed")
```

## 🚀 快速上手

下面是一个最小的示例，展示如何在您的项目中使用 CUnit。

**测试源文件**

将以下代码保存为 `main_test.c`：

```c
#include "cunit.h"

int add(int a, int b) {
    return a + b;
}

int main(void) {
    assert_int_eq(add(2, 2), 4);
    assert_true(add(0, 0) == 0, "test add(0,0) == 0");
    assert_false(add(1, 2) == 4, "test add(1,2) != 4");

    cunit_pass();
}
```

**CMake 配置文件**

在 `main_test.c` 相同的目录下，创建 `CMakeLists.txt` 文件：

```cmake
cmake_minimum_required(VERSION 3.12)
project(MinimalTest)

include(FetchContent)
FetchContent_Declare(
  CUnit
  GIT_REPOSITORY https://github.com/tayne3/CUnit.git
  GIT_TAG v0.1.4
)
FetchContent_MakeAvailable(CUnit)

enable_testing()
add_executable(MinimalTest main_test.c)
target_link_libraries(MinimalTest PRIVATE cunit::cunit)
add_test(NAME MinimalTest COMMAND MinimalTest)
set_tests_properties(MinimalTest PROPERTIES FAIL_REGULAR_EXPRESSION "failed")
```

**构建和运行**

打开终端，然后执行以下命令：

```sh
mkdir build
cd build
cmake ..
make
make test
```
