/*
 * MIT License
 *
 * Copyright (c) 2025 tayne3
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 * 2. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */
#ifndef CUNIT_SUITE_H
#define CUNIT_SUITE_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                              TYPE DEFINITIONS                              */
/* ========================================================================== */

typedef struct cunit_test  cunit_test_t;
typedef struct cunit_suite cunit_suite_t;

/**
 * @brief Function pointer type for test functions
 */
typedef void (*cunit_test_func_t)(void);

/**
 * @brief Function pointer type for setup functions
 */
typedef void (*cunit_setup_func_t)(void);

/**
 * @brief Function pointer type for teardown functions
 */
typedef void (*cunit_teardown_func_t)(void);

/**
 * @brief Error handling modes for test execution
 */
typedef enum {
	CUNIT_ERROR_MODE_COLLECT = 0, /**< Collect all errors (default)*/
	CUNIT_ERROR_MODE_FAIL_FAST,   /**< Stop on first error */
} cunit_error_mode_t;

/* ========================================================================== */
/*                               CORE API                                     */
/* ========================================================================== */

/**
 * @brief Initialize the cunit framework
 * @note This function is thread-safe and can be called multiple times
 */
void cunit_init(void);

/**
 * @brief Clean up all cunit resources
 * @warning Call this only after all tests have completed
 */
void cunit_cleanup(void);

/**
 * @brief Create a new test suite
 * @param name Suite name (must not be NULL)
 * @param setup Optional setup function (can be NULL)
 * @param teardown Optional teardown function (can be NULL)
 */
void cunit_suite(const char *name, cunit_setup_func_t setup, cunit_teardown_func_t teardown);

/**
 * @brief Add a test to the current suite
 * @param name Test name (must not be NULL)
 * @param test_func Test function pointer (must not be NULL)
 * @note Must be called after cunit_suite() or inside CUNIT_SUITE_BEGIN block
 */
void cunit_test(const char *name, cunit_test_func_t test_func);

/**
 * @brief Run all registered test suites
 * @return Number of failed tests (0 = all tests passed)
 */
int cunit_run(void);

/**
 * @brief Run a specific test suite by name
 * @param suite_name Name of the suite to run
 * @return Number of failed tests in the suite (-1 if suite not found)
 */
int cunit_run_suite(const char *suite_name);

/**
 * @brief Set error handling mode
 * @param mode Error handling mode
 */
void cunit_set_error_mode(cunit_error_mode_t mode);

/* ========================================================================== */
/*                              QUERY API                                     */
/* ========================================================================== */

/**
 * @brief Get total number of registered tests
 * @return Total test count across all suites
 */
int cunit_test_count(void);

/**
 * @brief Get total number of failed tests
 * @return Number of failed tests from last run
 */
int cunit_failure_count(void);

/**
 * @brief Get total number of registered suites
 * @return Total suite count
 */
int cunit_suite_count(void);

/* ========================================================================== */
/*                            STRUCTURED API                                  */
/* ========================================================================== */

/**
 * @brief Begin a test suite definition block
 * @param name Suite name
 * @param setup_func Optional setup function (can be NULL)
 * @param teardown_func Optional teardown function (can be NULL)
 *
 * @note Must be paired with CUNIT_SUITE_END()
 * @example
 * @code
 * CUNIT_SUITE_BEGIN("String Tests", NULL, NULL)
 *     CUNIT_TEST("String Length", test_strlen)
 *     CUNIT_TEST("String Compare", test_strcmp)
 * CUNIT_SUITE_END()
 * @endcode
 */
#define CUNIT_SUITE_BEGIN(name, setup_func, teardown_func) \
	do {                                                   \
		cunit_suite(name, setup_func, teardown_func);

/**
 * @brief Add a test to the current suite block
 * @param name Test name
 * @param func Test function
 */
#define CUNIT_TEST(name, func) cunit_test(name, func);

/**
 * @brief End a test suite definition block
 * @note Must be paired with CUNIT_SUITE_BEGIN()
 */
#define CUNIT_SUITE_END() \
	}                     \
	while (0);

#ifdef __cplusplus
}
#endif

#endif /* CUNIT_SUITE_H */
