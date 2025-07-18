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
#ifndef CUNIT_COMPARE_H
#define CUNIT_COMPARE_H

#include "value.h"
#include "ctx.h"

#ifdef __cplusplus
extern "C" {
#endif

// comparison flags
#define CUnit_Equal        0x01
#define CUnit_Less         0x02
#define CUnit_LessEqual    0x03
#define CUnit_Greater      0x04
#define CUnit_GreaterEqual 0x05
#define CUnit_NotEqual     0x06

void __cunit_pass(const cunit_context_t ctx);
void __cunit_fatal(const cunit_context_t ctx);

void __cunit_value_print(const cunit_value_t *self);
int __cunit_value_compare(const cunit_value_t *l, const cunit_value_t *r);

bool __cunit_compare_bool(const cunit_context_t ctx, bool l, bool r, int cond, const char *format, ...);
bool __cunit_compare_char(const cunit_context_t ctx, char l, char r, int cond, const char *format, ...);
bool __cunit_compare_float(const cunit_context_t ctx, float l, float r, int cond, const char *format, ...);
bool __cunit_compare_double(const cunit_context_t ctx, double l, double r, int cond, const char *format, ...);
bool __cunit_compare_ptr(const cunit_context_t ctx, const void *l, const void *r, int cond, const char *format, ...);
bool __cunit_check_null(const cunit_context_t ctx, const void *p, const char *format, ...);
bool __cunit_check_not_null(const cunit_context_t ctx, const void *p, const char *format, ...);

bool __cunit_check_str(const cunit_context_t ctx, const char *l, const char *r, bool equal, const char *format, ...);
bool __cunit_check_str_n(const cunit_context_t ctx, const char *l, const char *r, size_t size, const char *format, ...);
bool __cunit_check_str_case(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...);
bool __cunit_check_str_hex(const cunit_context_t ctx, const uint8_t *l, const uint8_t *r, size_t size, const char *format, ...);

bool __cunit_compare_int(const cunit_context_t ctx, int l, int r, int cond, const char *format, ...);
bool __cunit_compare_int8(const cunit_context_t ctx, int8_t l, int8_t r, int cond, const char *format, ...);
bool __cunit_compare_int16(const cunit_context_t ctx, int16_t l, int16_t r, int cond, const char *format, ...);
bool __cunit_compare_int32(const cunit_context_t ctx, int32_t l, int32_t r, int cond, const char *format, ...);
bool __cunit_compare_int64(const cunit_context_t ctx, int64_t l, int64_t r, int cond, const char *format, ...);
bool __cunit_compare_uint(const cunit_context_t ctx, unsigned l, unsigned r, int cond, const char *format, ...);
bool __cunit_compare_uint8(const cunit_context_t ctx, uint8_t l, uint8_t r, int cond, const char *format, ...);
bool __cunit_compare_uint16(const cunit_context_t ctx, uint16_t l, uint16_t r, int cond, const char *format, ...);
bool __cunit_compare_uint32(const cunit_context_t ctx, uint32_t l, uint32_t r, int cond, const char *format, ...);
bool __cunit_compare_uint64(const cunit_context_t ctx, uint64_t l, uint64_t r, int cond, const char *format, ...);

bool __cunit_check_any_in_array(const cunit_context_t ctx, const cunit_value_t value, const void *array, size_t size, const char *format, ...);
bool __cunit_check_any_not_in_array(const cunit_context_t ctx, const cunit_value_t value, const void *array, size_t size, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif  // CUNIT_COMPARE_H
