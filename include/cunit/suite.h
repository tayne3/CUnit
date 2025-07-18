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

typedef struct cunit_test       cunit_test_t;
typedef struct cunit_test_suite cunit_test_suite_t;

typedef void (*cunit_test_func_t)(void);
typedef void (*cunit_setup_func_t)(void);
typedef void (*cunit_teardown_func_t)(void);

// 错误处理模式
typedef enum {
	CUNIT_ERROR_MODE_IGNORE = 0,
	CUNIT_ERROR_MODE_FAIL_FAST,
	CUNIT_ERROR_MODE_COLLECT,
} cunit_error_mode_t;

void cunit_init(void);
void cunit_cleanup(void);
void cunit_add_test_suite(const char *name, cunit_setup_func_t setup, cunit_teardown_func_t teardown);
void cunit_add_test(const char *name, cunit_test_func_t test_func);
int  cunit_run(void);
int  cunit_run_suite(const char *suite_name);
void cunit_set_error_mode(cunit_error_mode_t mode);

int cunit_get_number_of_tests(void);
int cunit_get_number_of_failures(void);
int cunit_get_number_of_suites(void);

#ifdef __cplusplus
}
#endif

#endif  // CUNIT_SUITE_H
