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
#ifndef CUNIT_H
#define CUNIT_H

#ifdef __cplusplus
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#else
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

// -------------------------[base definition]-------------------------

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off

// newline
# ifndef STR_NEWLINE
#   ifdef _MSC_VER
#       define STR_NEWLINE      "\r\n"
#   else
#       define STR_NEWLINE      "\n"
#   endif
# endif
// empty string
# ifndef STR_NULL
#   define STR_NULL             ""
# endif
// string is empty
# ifndef STR_ISEMPTY
#   define STR_ISEMPTY(_s) 	    (!(_s) || !*(const char *)(_s))
# endif

# ifndef __GNUC_PREREQ
# 	define __GNUC_PREREQ(a, b)	0
# endif
	
# if defined __cplusplus ? __GNUC_PREREQ (2, 6) : __GNUC_PREREQ (2, 4)
#   define __cunit_func__		__extension__ __PRETTY_FUNCTION__
#	define __cunit_file__		__FILE__
#	define __cunit_line__		__LINE__
# elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	define __cunit_func__		__func__
#	define __cunit_file__      __FILE__
#	define __cunit_line__      __LINE__
# elif defined(__GNUC__)
#	define __cunit_func__      __FUNCTION__
#	define __cunit_file__      __FILE__
#	define __cunit_line__      __LINE__
# elif defined(_MSC_VER)
#	define __cunit_func__      __FUNCTION__
#	define __cunit_file__      __FILE__
#	define __cunit_line__      __LINE__
# elif defined(__TINYC__)
#	define __cunit_func__      __func__
#	define __cunit_file__      __FILE__
#	define __cunit_line__      __LINE__
# else
#	define __cunit_func__      "(nil)"
#	define __cunit_file__      "(nil)"
#	define __cunit_line__      0
# endif

// clang-format on

#ifdef __cplusplus
}
#endif

// -------------------------[cunit context]-------------------------

#ifdef __cplusplus
extern "C" {
#endif
typedef struct cunit_context {
	const char *file;
	const char *func;
	int         line;
} cunit_context_t;
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

// -------------------------[cunit any]-------------------------

#ifdef __cplusplus
extern "C" {
#endif

enum cunit_type {
	CUnitType_Invalid = 0,
	CUnitType_Bool,
	CUnitType_Char,
	CUnitType_Float32,
	CUnitType_Float64,
	CUnitType_String,
	CUnitType_Pointer,
	CUnitType_Int,
	CUnitType_Int8,
	CUnitType_Int16,
	CUnitType_Int32,
	CUnitType_Int64,
	CUnitType_Uint,
	CUnitType_Uint8,
	CUnitType_Uint16,
	CUnitType_Uint32,
	CUnitType_Uint64,
};

typedef struct cunit_value {
	union {
		bool     b;
		char     c;
		float    f32;
		double   f64;
		char    *str;
		void    *ptr;
		int      i;
		int8_t   i8;
		int16_t  i16;
		int32_t  i32;
		int64_t  i64;
		unsigned u;
		uint8_t  u8;
		uint16_t u16;
		uint32_t u32;
		uint64_t u64;
	} d;
	enum cunit_type type;
} cunit_value_t;

#define cunit_value_get_bool(_any)    ((_any).d.b)
#define cunit_value_get_char(_any)    ((_any).d.c)
#define cunit_value_get_float(_any)   ((_any).d.f32)
#define cunit_value_get_double(_any)  ((_any).d.f64)
#define cunit_value_get_string(_any)  ((_any).d.str)
#define cunit_value_get_pointer(_any) ((_any).d.ptr)
#define cunit_value_get_int(_any)     ((_any).d.i)
#define cunit_value_get_int8(_any)    ((_any).d.i8)
#define cunit_value_get_int16(_any)   ((_any).d.i16)
#define cunit_value_get_int32(_any)   ((_any).d.i32)
#define cunit_value_get_int64(_any)   ((_any).d.i64)
#define cunit_value_get_uint(_any)    ((_any).d.u)
#define cunit_value_get_uint8(_any)   ((_any).d.u8)
#define cunit_value_get_uint16(_any)  ((_any).d.u16)
#define cunit_value_get_uint32(_any)  ((_any).d.u32)
#define cunit_value_get_uint64(_any)  ((_any).d.u64)

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#define __cunit_value_init(_v, _type) \
	do {                              \
		cunit_value_t any;            \
		any.d._v = _v;                \
		any.type = _type;             \
		return any;                   \
	} while (0)

static inline cunit_value_t __cunit_value_init_bool(bool b) { __cunit_value_init(b, CUnitType_Bool); }
static inline cunit_value_t __cunit_value_init_char(char c) { __cunit_value_init(c, CUnitType_Char); }
static inline cunit_value_t __cunit_value_init_float(float f32) { __cunit_value_init(f32, CUnitType_Float32); }
static inline cunit_value_t __cunit_value_init_double(double f64) { __cunit_value_init(f64, CUnitType_Float64); }
static inline cunit_value_t __cunit_value_init_str(char *str) { __cunit_value_init(str, CUnitType_String); }
static inline cunit_value_t __cunit_value_init_ptr(void *ptr) { __cunit_value_init(ptr, CUnitType_Pointer); }
static inline cunit_value_t __cunit_value_init_int(int i) { __cunit_value_init(i, CUnitType_Int); }
static inline cunit_value_t __cunit_value_init_int8(int8_t i8) { __cunit_value_init(i8, CUnitType_Int8); }
static inline cunit_value_t __cunit_value_init_int16(int16_t i16) { __cunit_value_init(i16, CUnitType_Int16); }
static inline cunit_value_t __cunit_value_init_int32(int32_t i32) { __cunit_value_init(i32, CUnitType_Int32); }
static inline cunit_value_t __cunit_value_init_int64(int64_t i64) { __cunit_value_init(i64, CUnitType_Int64); }
static inline cunit_value_t __cunit_value_init_uint(unsigned u) { __cunit_value_init(u, CUnitType_Uint); }
static inline cunit_value_t __cunit_value_init_uint8(uint8_t u8) { __cunit_value_init(u8, CUnitType_Uint8); }
static inline cunit_value_t __cunit_value_init_uint16(uint16_t u16) { __cunit_value_init(u16, CUnitType_Uint16); }
static inline cunit_value_t __cunit_value_init_uint32(uint32_t u32) { __cunit_value_init(u32, CUnitType_Uint32); }
static inline cunit_value_t __cunit_value_init_uint64(uint64_t u64) { __cunit_value_init(u64, CUnitType_Uint64); }

#define CUNIT_VALUE_BOOL(_x)    __cunit_value_init_bool((bool)(_x))
#define CUNIT_VALUE_CHAR(_x)    __cunit_value_init_char((char)(_x))
#define CUNIT_VALUE_FLOAT(_x)   __cunit_value_init_float((float)(_x))
#define CUNIT_VALUE_DOUBLE(_x)  __cunit_value_init_double((double)(_x))
#define CUNIT_VALUE_STRING(_x)  __cunit_value_init_str((char *)(_x))
#define CUNIT_VALUE_POINTER(_x) __cunit_value_init_ptr((void *)(_x))
#define CUNIT_VALUE_INT(_x)     __cunit_value_init_int((int)(_x))
#define CUNIT_VALUE_INT8(_x)    __cunit_value_init_int8((int8_t)(_x))
#define CUNIT_VALUE_INT16(_x)   __cunit_value_init_int16((int16_t)(_x))
#define CUNIT_VALUE_INT32(_x)   __cunit_value_init_int32((int32_t)(_x))
#define CUNIT_VALUE_INT64(_x)   __cunit_value_init_int64((int64_t)(_x))
#define CUNIT_VALUE_UINT(_x)    __cunit_value_init_uint((unsigned)(_x))
#define CUNIT_VALUE_UINT8(_x)   __cunit_value_init_uint8((uint8_t)(_x))
#define CUNIT_VALUE_UINT16(_x)  __cunit_value_init_uint16((uint16_t)(_x))
#define CUNIT_VALUE_UINT32(_x)  __cunit_value_init_uint32((uint32_t)(_x))
#define CUNIT_VALUE_UINT64(_x)  __cunit_value_init_uint64((uint64_t)(_x))
#else

// clang-format off
#define CUNIT_VALUE_INIT_BOOL(_x)    { .d = {.b = (bool)(_x)}, .type = CUnitType_Bool }
#define CUNIT_VALUE_INIT_CHAR(_x)    { .d = {.c = (char)(_x)}, .type = CUnitType_Char }
#define CUNIT_VALUE_INIT_FLOAT(_x)   { .d = {.f32 = (float)(_x)}, .type = CUnitType_Float32 }
#define CUNIT_VALUE_INIT_DOUBLE(_x)  { .d = {.f64 = (double)(_x)}, .type = CUnitType_Float64 }
#define CUNIT_VALUE_INIT_STRING(_x)  { .d = {.str = (char *)(_x)}, .type = CUnitType_String }
#define CUNIT_VALUE_INIT_POINTER(_x) { .d = {.ptr = (void *)(_x)}, .type = CUnitType_Pointer }
#define CUNIT_VALUE_INIT_INT(_x)     { .d = {.i = (int)(_x)}, .type = CUnitType_Int }
#define CUNIT_VALUE_INIT_INT8(_x)    { .d = {.i8 = (int8_t)(_x)}, .type = CUnitType_Int8 }
#define CUNIT_VALUE_INIT_INT16(_x)   { .d = {.i16 = (int16_t)(_x)}, .type = CUnitType_Int16 }
#define CUNIT_VALUE_INIT_INT32(_x)   { .d = {.i32 = (int32_t)(_x)}, .type = CUnitType_Int32 }
#define CUNIT_VALUE_INIT_INT64(_x)   { .d = {.i64 = (int64_t)(_x)}, .type = CUnitType_Int64 }
#define CUNIT_VALUE_INIT_UINT(_x)    { .d = {.u = (unsigned)(_x)}, .type = CUnitType_Uint }
#define CUNIT_VALUE_INIT_UINT8(_x)   { .d = {.u8 = (uint8_t)(_x)}, .type = CUnitType_Uint8 }
#define CUNIT_VALUE_INIT_UINT16(_x)  { .d = {.u16 = (uint16_t)(_x)}, .type = CUnitType_Uint16 }
#define CUNIT_VALUE_INIT_UINT32(_x)  { .d = {.u32 = (uint32_t)(_x)}, .type = CUnitType_Uint32 }
#define CUNIT_VALUE_INIT_UINT64(_x)  { .d = {.u64 = (uint64_t)(_x)}, .type = CUnitType_Uint64 }
// clang-format on

#define CUNIT_VALUE_BOOL(_x)    ((cunit_value_t)CUNIT_VALUE_INIT_BOOL(_x))
#define CUNIT_VALUE_CHAR(_x)    ((cunit_value_t)CUNIT_VALUE_INIT_CHAR(_x))
#define CUNIT_VALUE_FLOAT(_x)   ((cunit_value_t)CUNIT_VALUE_INIT_FLOAT(_x))
#define CUNIT_VALUE_DOUBLE(_x)  ((cunit_value_t)CUNIT_VALUE_INIT_DOUBLE(_x))
#define CUNIT_VALUE_STRING(_x)  ((cunit_value_t)CUNIT_VALUE_INIT_STRING(_x))
#define CUNIT_VALUE_POINTER(_x) ((cunit_value_t)CUNIT_VALUE_INIT_POINTER(_x))
#define CUNIT_VALUE_INT(_x)     ((cunit_value_t)CUNIT_VALUE_INIT_INT(_x))
#define CUNIT_VALUE_INT8(_x)    ((cunit_value_t)CUNIT_VALUE_INIT_INT8(_x))
#define CUNIT_VALUE_INT16(_x)   ((cunit_value_t)CUNIT_VALUE_INIT_INT16(_x))
#define CUNIT_VALUE_INT32(_x)   ((cunit_value_t)CUNIT_VALUE_INIT_INT32(_x))
#define CUNIT_VALUE_INT64(_x)   ((cunit_value_t)CUNIT_VALUE_INIT_INT64(_x))
#define CUNIT_VALUE_UINT(_x)    ((cunit_value_t)CUNIT_VALUE_INIT_UINT(_x))
#define CUNIT_VALUE_UINT8(_x)   ((cunit_value_t)CUNIT_VALUE_INIT_UINT8(_x))
#define CUNIT_VALUE_UINT16(_x)  ((cunit_value_t)CUNIT_VALUE_INIT_UINT16(_x))
#define CUNIT_VALUE_UINT32(_x)  ((cunit_value_t)CUNIT_VALUE_INIT_UINT32(_x))
#define CUNIT_VALUE_UINT64(_x)  ((cunit_value_t)CUNIT_VALUE_INIT_UINT64(_x))
#endif

// -------------------------[cunit assert]-------------------------

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

#define ___cunit_assert_check_1(__func, __1, ...)         \
	do {                                                  \
		if (!__func(__1, __VA_ARGS__)) { cunit_fatal(); } \
	} while (0)
#define ___cunit_assert_check_2(__func, __1, __2, ...)         \
	do {                                                       \
		if (!__func(__1, __2, __VA_ARGS__)) { cunit_fatal(); } \
	} while (0)
#define ___cunit_assert_check_3(__func, __1, __2, __3, ...)         \
	do {                                                            \
		if (!__func(__1, __2, __3, __VA_ARGS__)) { cunit_fatal(); } \
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

// -------------------------[cunit aliases]-------------------------

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

#define cunit_pass()  __cunit_pass(CUNIT_CTX_CURR)
#define cunit_fatal() __cunit_fatal(CUNIT_CTX_CURR)

// -------------------------[cunit private functions]-------------------------

const char *__cunit_relative(const char *abs_path);
void        __cunit_pass(const cunit_context_t ctx);
void        __cunit_fatal(const cunit_context_t ctx);

bool __cunit_compare_bool(const cunit_context_t ctx, bool l, bool r, int cond, const char *format, ...);
bool __cunit_compare_char(const cunit_context_t ctx, char l, char r, int cond, const char *format, ...);
bool __cunit_compare_ptr(const cunit_context_t ctx, const void *l, const void *r, int cond, const char *format, ...);
bool __cunit_check_null(const cunit_context_t ctx, const void *p, const char *format, ...);
bool __cunit_check_not_null(const cunit_context_t ctx, const void *p, const char *format, ...);

bool __cunit_check_str(const cunit_context_t ctx, const char *l, const char *r, bool equal, const char *format, ...);
bool __cunit_check_str_n(const cunit_context_t ctx, const char *l, const char *r, size_t size, const char *format, ...);
bool __cunit_check_str_case(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...);
bool __cunit_check_str_hex(const cunit_context_t ctx, const uint8_t *l, const uint8_t *r, size_t size, const char *format, ...);

bool __cunit_compare_float(const cunit_context_t ctx, float l, float r, int cond, const char *format, ...);
bool __cunit_compare_double(const cunit_context_t ctx, double l, double r, int cond, const char *format, ...);
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
#endif  // CUNIT_H
