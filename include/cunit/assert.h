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
#ifndef CUNIT_ASSERT_H
#define CUNIT_ASSERT_H

#include "compare.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ___cunit_assert_check_1(__func, __1, ...)                         \
	do {                                                                  \
		if (!__func(__1, __VA_ARGS__)) { __cunit_fatal(CUNIT_CTX_CURR); } \
	} while (0)
#define ___cunit_assert_check_2(__func, __1, __2, ...)                         \
	do {                                                                       \
		if (!__func(__1, __2, __VA_ARGS__)) { __cunit_fatal(CUNIT_CTX_CURR); } \
	} while (0)
#define ___cunit_assert_check_3(__func, __1, __2, __3, ...)                         \
	do {                                                                            \
		if (!__func(__1, __2, __3, __VA_ARGS__)) { __cunit_fatal(CUNIT_CTX_CURR); } \
	} while (0)

#define ___cunit_check_bool_compare(__l, __r, ...)           __cunit_compare_bool(CUNIT_CTX_CURR, (__l), (__r), CUnit_Equal, STR_NULL __VA_ARGS__)
#define ___cunit_check_char_compare(__l, __r, ...)           __cunit_compare_char(CUNIT_CTX_CURR, (__l), (__r), CUnit_Equal, STR_NULL __VA_ARGS__)
#define ___cunit_check_ptr_compare(__l, __r, __cond, ...)    __cunit_compare_ptr(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_float_compare(__l, __r, __cond, ...)  __cunit_compare_float(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_double_compare(__l, __r, __cond, ...) __cunit_compare_double(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)

#define ___cunit_check_int8_compare(__l, __r, __cond, ...)  __cunit_compare_int8(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_int16_compare(__l, __r, __cond, ...) __cunit_compare_int16(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_int32_compare(__l, __r, __cond, ...) __cunit_compare_int32(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_int64_compare(__l, __r, __cond, ...) __cunit_compare_int64(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)

#define ___cunit_check_uint8_compare(__l, __r, __cond, ...)  __cunit_compare_uint8(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_uint16_compare(__l, __r, __cond, ...) __cunit_compare_uint16(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_uint32_compare(__l, __r, __cond, ...) __cunit_compare_uint32(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)
#define ___cunit_check_uint64_compare(__l, __r, __cond, ...) __cunit_compare_uint64(CUNIT_CTX_CURR, (__l), (__r), (__cond), STR_NULL __VA_ARGS__)

#define check_bool(__l, __r, ...) ___cunit_check_bool_compare(__l, __r, __VA_ARGS__)
#define check_true(__v, ...)      ___cunit_check_bool_compare(__v, true, __VA_ARGS__)
#define check_false(__v, ...)     ___cunit_check_bool_compare(__v, false, __VA_ARGS__)

#define assert_bool(__l, __r, ...) ___cunit_assert_check_2(check_bool, __l, __r, __VA_ARGS__)
#define assert_true(__v, ...)      ___cunit_assert_check_1(check_true, __v, __VA_ARGS__)
#define assert_false(__v, ...)     ___cunit_assert_check_1(check_false, __v, __VA_ARGS__)

#define check_char(__l, __r, ...)  ___cunit_check_char_compare(__l, __r, __VA_ARGS__)
#define assert_char(__l, __r, ...) ___cunit_assert_check_2(check_char, __l, __r, __VA_ARGS__)

#define check_str_eq(__l, __r, ...)       __cunit_check_str(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), true, STR_NULL __VA_ARGS__)
#define check_str_ne(__l, __r, ...)       __cunit_check_str(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), false, STR_NULL __VA_ARGS__)
#define check_str_n(__l, __r, __n, ...)   __cunit_check_str_n(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), (__n), STR_NULL __VA_ARGS__)
#define check_str_case(__l, __r, ...)     __cunit_check_str_case(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), STR_NULL __VA_ARGS__)
#define check_str_hex(__l, __r, __n, ...) __cunit_check_str_hex(CUNIT_CTX_CURR, (const uint8_t *)(__l), (const uint8_t *)(__r), (__n), STR_NULL __VA_ARGS__)

#define assert_str_eq(__l, __r, ...)       ___cunit_assert_check_2(check_str_eq, __l, __r, __VA_ARGS__)
#define assert_str_nq(__l, __r, ...)       ___cunit_assert_check_2(check_str_ne, __l, __r, __VA_ARGS__)
#define assert_str_n(__l, __r, __n, ...)   ___cunit_assert_check_3(check_str_n, __l, __r, __n, __VA_ARGS__)
#define assert_str_case(__l, __r, ...)     ___cunit_assert_check_2(check_str_case, __l, __r, __VA_ARGS__)
#define assert_str_hex(__l, __r, __n, ...) ___cunit_assert_check_3(check_str_hex, __l, __r, __n, __VA_ARGS__)

#define check_ptr_eq(__l, __r, ...) ___cunit_check_ptr_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_ptr_ne(__l, __r, ...) ___cunit_check_ptr_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)

#define assert_ptr_eq(__l, __r, ...) ___cunit_assert_check_2(check_ptr_eq, __l, __r, __VA_ARGS__)
#define assert_ptr_ne(__l, __r, ...) ___cunit_assert_check_2(check_ptr_ne, __l, __r, __VA_ARGS__)

#define check_null(__p, ...)  __cunit_check_null(CUNIT_CTX_CURR, (const void *)(__p), STR_NULL __VA_ARGS__)
#define assert_null(__p, ...) ___cunit_assert_check_1(check_null, __p, __VA_ARGS__)

#define check_not_null(__p, ...)  __cunit_check_not_null(CUNIT_CTX_CURR, (const void *)(__p), STR_NULL __VA_ARGS__)
#define assert_not_null(__p, ...) ___cunit_assert_check_1(check_not_null, __p, __VA_ARGS__)

#define check_float_eq(__l, __r, ...) ___cunit_check_float_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_float_ne(__l, __r, ...) ___cunit_check_float_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_float_lt(__l, __r, ...) ___cunit_check_float_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_float_le(__l, __r, ...) ___cunit_check_float_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_float_gt(__l, __r, ...) ___cunit_check_float_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_float_ge(__l, __r, ...) ___cunit_check_float_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_float_eq(__l, __r, ...) ___cunit_assert_check_2(check_float_eq, __l, __r, __VA_ARGS__)
#define assert_float_ne(__l, __r, ...) ___cunit_assert_check_2(check_float_ne, __l, __r, __VA_ARGS__)
#define assert_float_lt(__l, __r, ...) ___cunit_assert_check_2(check_float_lt, __l, __r, __VA_ARGS__)
#define assert_float_le(__l, __r, ...) ___cunit_assert_check_2(check_float_le, __l, __r, __VA_ARGS__)
#define assert_float_gt(__l, __r, ...) ___cunit_assert_check_2(check_float_gt, __l, __r, __VA_ARGS__)
#define assert_float_ge(__l, __r, ...) ___cunit_assert_check_2(check_float_ge, __l, __r, __VA_ARGS__)

#define check_float32_eq check_float_eq
#define check_float32_ne check_float_ne
#define check_float32_lt check_float_lt
#define check_float32_le check_float_le
#define check_float32_gt check_float_gt
#define check_float32_ge check_float_ge

#define assert_float32_eq assert_float_eq
#define assert_float32_ne assert_float_ne
#define assert_float32_lt assert_float_lt
#define assert_float32_le assert_float_le
#define assert_float32_gt assert_float_gt
#define assert_float32_ge assert_float_ge

#define check_double_eq(__l, __r, ...) ___cunit_check_double_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_double_ne(__l, __r, ...) ___cunit_check_double_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_double_lt(__l, __r, ...) ___cunit_check_double_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_double_le(__l, __r, ...) ___cunit_check_double_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_double_gt(__l, __r, ...) ___cunit_check_double_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_double_ge(__l, __r, ...) ___cunit_check_double_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_double_eq(__l, __r, ...) ___cunit_assert_check_2(check_double_eq, __l, __r, __VA_ARGS__)
#define assert_double_ne(__l, __r, ...) ___cunit_assert_check_2(check_double_ne, __l, __r, __VA_ARGS__)
#define assert_double_lt(__l, __r, ...) ___cunit_assert_check_2(check_double_lt, __l, __r, __VA_ARGS__)
#define assert_double_le(__l, __r, ...) ___cunit_assert_check_2(check_double_le, __l, __r, __VA_ARGS__)
#define assert_double_gt(__l, __r, ...) ___cunit_assert_check_2(check_double_gt, __l, __r, __VA_ARGS__)
#define assert_double_ge(__l, __r, ...) ___cunit_assert_check_2(check_double_ge, __l, __r, __VA_ARGS__)

#define check_float64_eq check_double_eq
#define check_float64_ne check_double_ne
#define check_float64_lt check_double_lt
#define check_float64_le check_double_le
#define check_float64_gt check_double_gt
#define check_float64_ge check_double_ge

#define assert_float64_eq assert_double_eq
#define assert_float64_ne assert_double_ne
#define assert_float64_lt assert_double_lt
#define assert_float64_le assert_double_le
#define assert_float64_gt assert_double_gt
#define assert_float64_ge assert_double_ge

#define check_int_eq(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_int_ne(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_int_lt(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_int_le(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_int_gt(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_int_ge(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_int_eq(__l, __r, ...) ___cunit_assert_check_2(check_int_eq, __l, __r, __VA_ARGS__)
#define assert_int_ne(__l, __r, ...) ___cunit_assert_check_2(check_int_ne, __l, __r, __VA_ARGS__)
#define assert_int_lt(__l, __r, ...) ___cunit_assert_check_2(check_int_lt, __l, __r, __VA_ARGS__)
#define assert_int_le(__l, __r, ...) ___cunit_assert_check_2(check_int_le, __l, __r, __VA_ARGS__)
#define assert_int_gt(__l, __r, ...) ___cunit_assert_check_2(check_int_gt, __l, __r, __VA_ARGS__)
#define assert_int_ge(__l, __r, ...) ___cunit_assert_check_2(check_int_ge, __l, __r, __VA_ARGS__)

#define check_int8_eq(__l, __r, ...) ___cunit_check_int8_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_int8_ne(__l, __r, ...) ___cunit_check_int8_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_int8_lt(__l, __r, ...) ___cunit_check_int8_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_int8_le(__l, __r, ...) ___cunit_check_int8_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_int8_gt(__l, __r, ...) ___cunit_check_int8_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_int8_ge(__l, __r, ...) ___cunit_check_int8_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_int8_eq(__l, __r, ...) ___cunit_assert_check_2(check_int8_eq, __l, __r, __VA_ARGS__)
#define assert_int8_ne(__l, __r, ...) ___cunit_assert_check_2(check_int8_ne, __l, __r, __VA_ARGS__)
#define assert_int8_lt(__l, __r, ...) ___cunit_assert_check_2(check_int8_lt, __l, __r, __VA_ARGS__)
#define assert_int8_le(__l, __r, ...) ___cunit_assert_check_2(check_int8_le, __l, __r, __VA_ARGS__)
#define assert_int8_gt(__l, __r, ...) ___cunit_assert_check_2(check_int8_gt, __l, __r, __VA_ARGS__)
#define assert_int8_ge(__l, __r, ...) ___cunit_assert_check_2(check_int8_ge, __l, __r, __VA_ARGS__)

#define check_int16_eq(__l, __r, ...) ___cunit_check_int16_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_int16_ne(__l, __r, ...) ___cunit_check_int16_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_int16_lt(__l, __r, ...) ___cunit_check_int16_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_int16_le(__l, __r, ...) ___cunit_check_int16_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_int16_gt(__l, __r, ...) ___cunit_check_int16_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_int16_ge(__l, __r, ...) ___cunit_check_int16_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_int16_eq(__l, __r, ...) ___cunit_assert_check_2(check_int16_eq, __l, __r, __VA_ARGS__)
#define assert_int16_ne(__l, __r, ...) ___cunit_assert_check_2(check_int16_ne, __l, __r, __VA_ARGS__)
#define assert_int16_lt(__l, __r, ...) ___cunit_assert_check_2(check_int16_lt, __l, __r, __VA_ARGS__)
#define assert_int16_le(__l, __r, ...) ___cunit_assert_check_2(check_int16_le, __l, __r, __VA_ARGS__)
#define assert_int16_gt(__l, __r, ...) ___cunit_assert_check_2(check_int16_gt, __l, __r, __VA_ARGS__)
#define assert_int16_ge(__l, __r, ...) ___cunit_assert_check_2(check_int16_ge, __l, __r, __VA_ARGS__)

#define check_int32_eq(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_int32_ne(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_int32_lt(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_int32_le(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_int32_gt(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_int32_ge(__l, __r, ...) ___cunit_check_int32_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_int32_eq(__l, __r, ...) ___cunit_assert_check_2(check_int32_eq, __l, __r, __VA_ARGS__)
#define assert_int32_ne(__l, __r, ...) ___cunit_assert_check_2(check_int32_ne, __l, __r, __VA_ARGS__)
#define assert_int32_lt(__l, __r, ...) ___cunit_assert_check_2(check_int32_lt, __l, __r, __VA_ARGS__)
#define assert_int32_le(__l, __r, ...) ___cunit_assert_check_2(check_int32_le, __l, __r, __VA_ARGS__)
#define assert_int32_gt(__l, __r, ...) ___cunit_assert_check_2(check_int32_gt, __l, __r, __VA_ARGS__)
#define assert_int32_ge(__l, __r, ...) ___cunit_assert_check_2(check_int32_ge, __l, __r, __VA_ARGS__)

#define check_int64_eq(__l, __r, ...) ___cunit_check_int64_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_int64_ne(__l, __r, ...) ___cunit_check_int64_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_int64_lt(__l, __r, ...) ___cunit_check_int64_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_int64_le(__l, __r, ...) ___cunit_check_int64_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_int64_gt(__l, __r, ...) ___cunit_check_int64_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_int64_ge(__l, __r, ...) ___cunit_check_int64_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_int64_eq(__l, __r, ...) ___cunit_assert_check_2(check_int64_eq, __l, __r, __VA_ARGS__)
#define assert_int64_ne(__l, __r, ...) ___cunit_assert_check_2(check_int64_ne, __l, __r, __VA_ARGS__)
#define assert_int64_lt(__l, __r, ...) ___cunit_assert_check_2(check_int64_lt, __l, __r, __VA_ARGS__)
#define assert_int64_le(__l, __r, ...) ___cunit_assert_check_2(check_int64_le, __l, __r, __VA_ARGS__)
#define assert_int64_gt(__l, __r, ...) ___cunit_assert_check_2(check_int64_gt, __l, __r, __VA_ARGS__)
#define assert_int64_ge(__l, __r, ...) ___cunit_assert_check_2(check_int64_ge, __l, __r, __VA_ARGS__)

#define check_uint_eq(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_uint_ne(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_uint_lt(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_uint_le(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_uint_gt(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_uint_ge(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_uint_eq(__l, __r, ...) ___cunit_assert_check_2(check_uint_eq, __l, __r, __VA_ARGS__)
#define assert_uint_ne(__l, __r, ...) ___cunit_assert_check_2(check_uint_ne, __l, __r, __VA_ARGS__)
#define assert_uint_lt(__l, __r, ...) ___cunit_assert_check_2(check_uint_lt, __l, __r, __VA_ARGS__)
#define assert_uint_le(__l, __r, ...) ___cunit_assert_check_2(check_uint_le, __l, __r, __VA_ARGS__)
#define assert_uint_gt(__l, __r, ...) ___cunit_assert_check_2(check_uint_gt, __l, __r, __VA_ARGS__)
#define assert_uint_ge(__l, __r, ...) ___cunit_assert_check_2(check_uint_ge, __l, __r, __VA_ARGS__)

#define check_uint8_eq(__l, __r, ...) ___cunit_check_uint8_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_uint8_ne(__l, __r, ...) ___cunit_check_uint8_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_uint8_lt(__l, __r, ...) ___cunit_check_uint8_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_uint8_le(__l, __r, ...) ___cunit_check_uint8_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_uint8_gt(__l, __r, ...) ___cunit_check_uint8_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_uint8_ge(__l, __r, ...) ___cunit_check_uint8_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_uint8_eq(__l, __r, ...) ___cunit_assert_check_2(check_uint8_eq, __l, __r, __VA_ARGS__)
#define assert_uint8_ne(__l, __r, ...) ___cunit_assert_check_2(check_uint8_ne, __l, __r, __VA_ARGS__)
#define assert_uint8_lt(__l, __r, ...) ___cunit_assert_check_2(check_uint8_lt, __l, __r, __VA_ARGS__)
#define assert_uint8_le(__l, __r, ...) ___cunit_assert_check_2(check_uint8_le, __l, __r, __VA_ARGS__)
#define assert_uint8_gt(__l, __r, ...) ___cunit_assert_check_2(check_uint8_gt, __l, __r, __VA_ARGS__)
#define assert_uint8_ge(__l, __r, ...) ___cunit_assert_check_2(check_uint8_ge, __l, __r, __VA_ARGS__)

#define check_uint16_eq(__l, __r, ...) ___cunit_check_uint16_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_uint16_ne(__l, __r, ...) ___cunit_check_uint16_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_uint16_lt(__l, __r, ...) ___cunit_check_uint16_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_uint16_le(__l, __r, ...) ___cunit_check_uint16_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_uint16_gt(__l, __r, ...) ___cunit_check_uint16_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_uint16_ge(__l, __r, ...) ___cunit_check_uint16_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_uint16_eq(__l, __r, ...) ___cunit_assert_check_2(check_uint16_eq, __l, __r, __VA_ARGS__)
#define assert_uint16_ne(__l, __r, ...) ___cunit_assert_check_2(check_uint16_ne, __l, __r, __VA_ARGS__)
#define assert_uint16_lt(__l, __r, ...) ___cunit_assert_check_2(check_uint16_lt, __l, __r, __VA_ARGS__)
#define assert_uint16_le(__l, __r, ...) ___cunit_assert_check_2(check_uint16_le, __l, __r, __VA_ARGS__)
#define assert_uint16_gt(__l, __r, ...) ___cunit_assert_check_2(check_uint16_gt, __l, __r, __VA_ARGS__)
#define assert_uint16_ge(__l, __r, ...) ___cunit_assert_check_2(check_uint16_ge, __l, __r, __VA_ARGS__)

#define check_uint32_eq(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_uint32_ne(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_uint32_lt(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_uint32_le(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_uint32_gt(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_uint32_ge(__l, __r, ...) ___cunit_check_uint32_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_uint32_eq(__l, __r, ...) ___cunit_assert_check_2(check_uint32_eq, __l, __r, __VA_ARGS__)
#define assert_uint32_ne(__l, __r, ...) ___cunit_assert_check_2(check_uint32_ne, __l, __r, __VA_ARGS__)
#define assert_uint32_lt(__l, __r, ...) ___cunit_assert_check_2(check_uint32_lt, __l, __r, __VA_ARGS__)
#define assert_uint32_le(__l, __r, ...) ___cunit_assert_check_2(check_uint32_le, __l, __r, __VA_ARGS__)
#define assert_uint32_gt(__l, __r, ...) ___cunit_assert_check_2(check_uint32_gt, __l, __r, __VA_ARGS__)
#define assert_uint32_ge(__l, __r, ...) ___cunit_assert_check_2(check_uint32_ge, __l, __r, __VA_ARGS__)

#define check_uint64_eq(__l, __r, ...) ___cunit_check_uint64_compare(__l, __r, CUnit_Equal, __VA_ARGS__)
#define check_uint64_ne(__l, __r, ...) ___cunit_check_uint64_compare(__l, __r, CUnit_NotEqual, __VA_ARGS__)
#define check_uint64_lt(__l, __r, ...) ___cunit_check_uint64_compare(__l, __r, CUnit_Less, __VA_ARGS__)
#define check_uint64_le(__l, __r, ...) ___cunit_check_uint64_compare(__l, __r, CUnit_LessEqual, __VA_ARGS__)
#define check_uint64_gt(__l, __r, ...) ___cunit_check_uint64_compare(__l, __r, CUnit_Greater, __VA_ARGS__)
#define check_uint64_ge(__l, __r, ...) ___cunit_check_uint64_compare(__l, __r, CUnit_GreaterEqual, __VA_ARGS__)

#define assert_uint64_eq(__l, __r, ...) ___cunit_assert_check_2(check_uint64_eq, __l, __r, __VA_ARGS__)
#define assert_uint64_ne(__l, __r, ...) ___cunit_assert_check_2(check_uint64_ne, __l, __r, __VA_ARGS__)
#define assert_uint64_lt(__l, __r, ...) ___cunit_assert_check_2(check_uint64_lt, __l, __r, __VA_ARGS__)
#define assert_uint64_le(__l, __r, ...) ___cunit_assert_check_2(check_uint64_le, __l, __r, __VA_ARGS__)
#define assert_uint64_gt(__l, __r, ...) ___cunit_assert_check_2(check_uint64_gt, __l, __r, __VA_ARGS__)
#define assert_uint64_ge(__l, __r, ...) ___cunit_assert_check_2(check_uint64_ge, __l, __r, __VA_ARGS__)

#define check_in_array(__value, __array, __size, ...) \
	__cunit_check_any_in_array(CUNIT_CTX_CURR, (__value), (const void *)(__array), (size_t)(__size), STR_NULL __VA_ARGS__)
#define assert_in_array(__value, __array, __size, ...) ___cunit_assert_check_3(check_in_array, __value, __array, __size, __VA_ARGS__)

#define check_not_in_array(__value, __array, __size, ...) \
	__cunit_check_any_not_in_array(CUNIT_CTX_CURR, (__value), (const void *)(__array), (size_t)(__size), STR_NULL __VA_ARGS__)
#define assert_not_in_array(__value, __array, __size, ...) ___cunit_assert_check_3(check_not_in_array, __value, __array, __size, __VA_ARGS__)

#define cunit_print(...)                                                                     \
	do {                                                                                     \
		printf("\033[37;2m%s:%d\033[0m ", __cunit_relative(__cunit_file__), __cunit_line__); \
		printf(__VA_ARGS__);                                                                 \
	} while (0)
#define cunit_println(...)                                                                   \
	do {                                                                                     \
		printf("\033[37;2m%s:%d\033[0m ", __cunit_relative(__cunit_file__), __cunit_line__); \
		printf(__VA_ARGS__);                                                                 \
		printf(STR_NEWLINE);                                                                 \
	} while (0)

#ifdef __cplusplus
}
#endif

#endif  // CUNIT_ASSERT_H
