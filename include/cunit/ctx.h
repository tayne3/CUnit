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
#ifndef CUNIT_CTX_H
#define CUNIT_CTX_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct cunit_context {
	const char *file;
	const char *func;
	int         line;
} cunit_context_t;

const char *__cunit_relative(const char *abs_path);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
static inline cunit_context_t __cunit_context_package(const char *file, const char *func, int line) {
	cunit_context_t ctx;
	ctx.file = file;
	ctx.func = func;
	ctx.line = line;
	return ctx;
}
#define CUNIT_CTX_CURR __cunit_context_package(__cunit_file__, __cunit_func__, __cunit_line__)
#else
#define CUNIT_CTX_CURR ((cunit_context_t){.file = __cunit_file__, .func = __cunit_func__, .line = __cunit_line__})
#endif

#endif  // CUNIT_CTX_H
