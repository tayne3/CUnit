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
extern "C" {
#endif

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------[base definition]-------------------------

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

// -------------------------[cunit any]-------------------------

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

typedef struct cunit_any {
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
} cunit_any_t;

// Initialization
#define CUNIT_ANY_INIT_SPECIFY(_x, _t) {.d = {.u64 = (uint64_t)(_x)}, .type = (_t)}

// clang-format off
#define CUNIT_ANY_INIT_INVALID 	   { .d = {.u64 = 0}, .type = CUnitType_Invalid }
#define CUNIT_ANY_INIT_BOOL(_x)    { .d = {.b = (bool)(_x)}, .type = CUnitType_Bool }
#define CUNIT_ANY_INIT_CHAR(_x)    { .d = {.c = (char)(_x)}, .type = CUnitType_Char }
#define CUNIT_ANY_INIT_FLOAT(_x)   { .d = {.f32 = (float)(_x)}, .type = CUnitType_Float32 }
#define CUNIT_ANY_INIT_DOUBLE(_x)  { .d = {.f64 = (double)(_x)}, .type = CUnitType_Float64 }
#define CUNIT_ANY_INIT_STRING(_x)  { .d = {.str = (char *)(_x)}, .type = CUnitType_String }
#define CUNIT_ANY_INIT_POINTER(_x) { .d = {.ptr = (void *)(_x)}, .type = CUnitType_Pointer }
#define CUNIT_ANY_INIT_INT(_x)     { .d = {.i = (int)(_x)}, .type = CUnitType_Int }
#define CUNIT_ANY_INIT_INT8(_x)    { .d = {.i8 = (int8_t)(_x)}, .type = CUnitType_Int8 }
#define CUNIT_ANY_INIT_INT16(_x)   { .d = {.i16 = (int16_t)(_x)}, .type = CUnitType_Int16 }
#define CUNIT_ANY_INIT_INT32(_x)   { .d = {.i32 = (int32_t)(_x)}, .type = CUnitType_Int32 }
#define CUNIT_ANY_INIT_INT64(_x)   { .d = {.i64 = (int64_t)(_x)}, .type = CUnitType_Int64 }
#define CUNIT_ANY_INIT_UINT(_x)    { .d = {.u = (unsigned)(_x)}, .type = CUnitType_Uint }
#define CUNIT_ANY_INIT_UINT8(_x)   { .d = {.u8 = (uint8_t)(_x)}, .type = CUnitType_Uint8 }
#define CUNIT_ANY_INIT_UINT16(_x)  { .d = {.u16 = (uint16_t)(_x)}, .type = CUnitType_Uint16 }
#define CUNIT_ANY_INIT_UINT32(_x)  { .d = {.u32 = (uint32_t)(_x)}, .type = CUnitType_Uint32 }
#define CUNIT_ANY_INIT_UINT64(_x)  { .d = {.u64 = (uint64_t)(_x)}, .type = CUnitType_Uint64 }
// clang-format on

#define CUNIT_ANY_SPECIFY(_x, _t) ((cunit_any_t)CUNIT_ANY_INIT_SPECIFY(_x, _t))
#define CUNIT_ANY_BOOL(_x)        ((cunit_any_t)CUNIT_ANY_INIT_BOOL(_x))
#define CUNIT_ANY_CHAR(_x)        ((cunit_any_t)CUNIT_ANY_INIT_CHAR(_x))
#define CUNIT_ANY_FLOAT(_x)       ((cunit_any_t)CUNIT_ANY_INIT_FLOAT(_x))
#define CUNIT_ANY_DOUBLE(_x)      ((cunit_any_t)CUNIT_ANY_INIT_DOUBLE(_x))
#define CUNIT_ANY_STRING(_x)      ((cunit_any_t)CUNIT_ANY_INIT_STRING(_x))
#define CUNIT_ANY_POINTER(_x)     ((cunit_any_t)CUNIT_ANY_INIT_POINTER(_x))
#define CUNIT_ANY_INT(_x)         ((cunit_any_t)CUNIT_ANY_INIT_INT(_x))
#define CUNIT_ANY_INT8(_x)        ((cunit_any_t)CUNIT_ANY_INIT_INT8(_x))
#define CUNIT_ANY_INT16(_x)       ((cunit_any_t)CUNIT_ANY_INIT_INT16(_x))
#define CUNIT_ANY_INT32(_x)       ((cunit_any_t)CUNIT_ANY_INIT_INT32(_x))
#define CUNIT_ANY_INT64(_x)       ((cunit_any_t)CUNIT_ANY_INIT_INT64(_x))
#define CUNIT_ANY_UINT(_x)        ((cunit_any_t)CUNIT_ANY_INIT_UINT(_x))
#define CUNIT_ANY_UINT8(_x)       ((cunit_any_t)CUNIT_ANY_INIT_UINT8(_x))
#define CUNIT_ANY_UINT16(_x)      ((cunit_any_t)CUNIT_ANY_INIT_UINT16(_x))
#define CUNIT_ANY_UINT32(_x)      ((cunit_any_t)CUNIT_ANY_INIT_UINT32(_x))
#define CUNIT_ANY_UINT64(_x)      ((cunit_any_t)CUNIT_ANY_INIT_UINT64(_x))

#define cunit_any_value_bool(_any)    ((_any).d.b)
#define cunit_any_value_char(_any)    ((_any).d.c)
#define cunit_any_value_float(_any)   ((_any).d.f32)
#define cunit_any_value_double(_any)  ((_any).d.f64)
#define cunit_any_value_string(_any)  ((_any).d.str)
#define cunit_any_value_pointer(_any) ((_any).d.ptr)
#define cunit_any_value_int(_any)     ((_any).d.i)
#define cunit_any_value_int8(_any)    ((_any).d.i8)
#define cunit_any_value_int16(_any)   ((_any).d.i16)
#define cunit_any_value_int32(_any)   ((_any).d.i32)
#define cunit_any_value_int64(_any)   ((_any).d.i64)
#define cunit_any_value_uint(_any)    ((_any).d.u)
#define cunit_any_value_uint8(_any)   ((_any).d.u8)
#define cunit_any_value_uint16(_any)  ((_any).d.u16)
#define cunit_any_value_uint32(_any)  ((_any).d.u32)
#define cunit_any_value_uint64(_any)  ((_any).d.u64)

// Print output
void cunit_any_print(const cunit_any_t *self);
// Compare result (-1=less than; 0=equal; 1=greater than; -2=error)
int cunit_any_compare(const cunit_any_t *l, const cunit_any_t *r);
// Swap
void cunit_any_swap(cunit_any_t *l, cunit_any_t *r);

// -------------------------[cunit context]-------------------------

typedef struct cunit_context {
	const char *file;
	const char *func;
	int         line;
} cunit_context_t;

#define CUNIT_CTX_INIT(_file, _func, _line) {.file = (_file), .func = (_func), .line = (_line)}
#define CUNIT_CTX_CURR                      ((cunit_context_t)CUNIT_CTX_INIT(__cunit_file__, __cunit_func__, __cunit_line__))

// -------------------------[cunit assert]-------------------------

// comparison flags
#define CUnit_Equal        0x01
#define CUnit_Less         0x02
#define CUnit_LessEqual    0x03
#define CUnit_Greater      0x04
#define CUnit_GreaterEqual 0x05
#define CUnit_NotEqual     0x06

#ifdef _MSC_VER

#define ___cunit_check_compare(__l, __r, __cond, ...) \
	__cunit_check_any_compare(CUNIT_CTX_CURR, __l, __r, __cond, STR_NULL __VA_ARGS__)

#define cunit_check_bool(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_BOOL(__l), CUNIT_ANY_BOOL(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_bool(__l, __r, ...)                \
	do {                                                \
		if (!cunit_check_bool(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                              \
		}                                               \
	} while (0)

#define cunit_check_true(__v, ...) \
	___cunit_check_compare(CUNIT_ANY_BOOL(__v), CUNIT_ANY_BOOL(true), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_true(__v, ...)                \
	do {                                           \
		if (!cunit_check_true(__v, __VA_ARGS__)) { \
			cunit_fatal();                         \
		}                                          \
	} while (0)

#define cunit_check_false(__v, ...) \
	___cunit_check_compare(CUNIT_ANY_BOOL(__v), CUNIT_ANY_BOOL(false), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_false(__v, ...)                \
	do {                                            \
		if (!cunit_check_false(__v, __VA_ARGS__)) { \
			cunit_fatal();                          \
		}                                           \
	} while (0)

#define cunit_check_char(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_CHAR(__l), CUNIT_ANY_CHAR(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_char(__l, __r, ...)                \
	do {                                                \
		if (!cunit_check_char(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                              \
		}                                               \
	} while (0)

#define cunit_check_int(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), __cond, __VA_ARGS__)
#define cunit_assert_int(__l, __r, __cond, ...)                \
	do {                                                       \
		if (!cunit_check_int(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_int_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_int_equal(__l, __r, ...)                \
	do {                                                     \
		if (!cunit_check_int_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                   \
		}                                                    \
	} while (0)
#define cunit_check_int_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_int_not_equal(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_int_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_int_less(__l, __r, ...)                \
	do {                                                    \
		if (!cunit_check_int_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                  \
		}                                                   \
	} while (0)
#define cunit_check_int_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_int_less_equal(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_int_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_int_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_int_greater(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_int_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_int_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_int_greater_equal(__l, __r, ...)                \
	do {                                                             \
		if (!cunit_check_int_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                           \
		}                                                            \
	} while (0)

#define cunit_check_int8(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), __cond, __VA_ARGS__)
#define cunit_assert_int8(__l, __r, __cond, ...)                \
	do {                                                        \
		if (!cunit_check_int8(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_int8_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_int8_equal(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_int8_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_int8_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_int8_not_equal(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_int8_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_int8_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_int8_less(__l, __r, ...)                \
	do {                                                     \
		if (!cunit_check_int8_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                   \
		}                                                    \
	} while (0)
#define cunit_check_int8_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_int8_less_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_int8_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_int8_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_int8_greater(__l, __r, ...)                \
	do {                                                        \
		if (!cunit_check_int8_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_int8_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_int8_greater_equal(__l, __r, ...)                \
	do {                                                              \
		if (!cunit_check_int8_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                            \
		}                                                             \
	} while (0)

#define cunit_check_int16(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), __cond, __VA_ARGS__)
#define cunit_assert_int16(__l, __r, __cond, ...)                \
	do {                                                         \
		if (!cunit_check_int16(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int16_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_int16_equal(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_int16_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_int16_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_int16_not_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_int16_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_int16_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_int16_less(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_int16_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_int16_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_int16_less_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_int16_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_int16_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_int16_greater(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_int16_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int16_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_int16_greater_equal(__l, __r, ...)                \
	do {                                                               \
		if (!cunit_check_int16_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                             \
		}                                                              \
	} while (0)

#define cunit_check_int32(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), __cond, __VA_ARGS__)
#define cunit_assert_int32(__l, __r, __cond, ...)                \
	do {                                                         \
		if (!cunit_check_int32(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int32_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_int32_equal(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_int32_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_int32_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_int32_not_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_int32_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_int32_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_int32_less(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_int32_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_int32_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_int32_less_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_int32_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_int32_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_int32_greater(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_int32_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int32_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_int32_greater_equal(__l, __r, ...)                \
	do {                                                               \
		if (!cunit_check_int32_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                             \
		}                                                              \
	} while (0)

#define cunit_check_int64(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), __cond, __VA_ARGS__)
#define cunit_assert_int64(__l, __r, __cond, ...)                \
	do {                                                         \
		if (!cunit_check_int64(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int64_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_int64_equal(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_int64_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_int64_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_int64_not_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_int64_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_int64_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_int64_less(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_int64_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_int64_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_int64_less_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_int64_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_int64_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_int64_greater(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_int64_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_int64_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_int64_greater_equal(__l, __r, ...)                \
	do {                                                               \
		if (!cunit_check_int64_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                             \
		}                                                              \
	} while (0)

#define cunit_check_uint(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), __cond, __VA_ARGS__)
#define cunit_assert_uint(__l, __r, __cond, ...)                \
	do {                                                        \
		if (!cunit_check_uint(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_uint_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_uint_equal(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_uint_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_uint_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_uint_not_equal(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_uint_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_uint_less(__l, __r, ...)                \
	do {                                                     \
		if (!cunit_check_uint_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                   \
		}                                                    \
	} while (0)
#define cunit_check_uint_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_uint_less_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_uint_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_uint_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_uint_greater(__l, __r, ...)                \
	do {                                                        \
		if (!cunit_check_uint_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_uint_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_uint_greater_equal(__l, __r, ...)                \
	do {                                                              \
		if (!cunit_check_uint_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                            \
		}                                                             \
	} while (0)

#define cunit_check_uint8(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), __cond, __VA_ARGS__)
#define cunit_assert_uint8(__l, __r, __cond, ...)                \
	do {                                                         \
		if (!cunit_check_uint8(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_uint8_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_uint8_equal(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_uint8_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_uint8_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_uint8_not_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_uint8_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_uint8_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_uint8_less(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_uint8_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_uint8_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_uint8_less_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_uint8_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_uint8_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_uint8_greater(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_uint8_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_uint8_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_uint8_greater_equal(__l, __r, ...)                \
	do {                                                               \
		if (!cunit_check_uint8_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                             \
		}                                                              \
	} while (0)

#define cunit_check_uint16(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), __cond, __VA_ARGS__)
#define cunit_assert_uint16(__l, __r, __cond, ...)                \
	do {                                                          \
		if (!cunit_check_uint16(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint16_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_uint16_equal(__l, __r, ...)                \
	do {                                                        \
		if (!cunit_check_uint16_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_uint16_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_uint16_not_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_uint16_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_uint16_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_uint16_less(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_uint16_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_uint16_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_uint16_less_equal(__l, __r, ...)                \
	do {                                                             \
		if (!cunit_check_uint16_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                           \
		}                                                            \
	} while (0)
#define cunit_check_uint16_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_uint16_greater(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_uint16_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint16_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_uint16_greater_equal(__l, __r, ...)                \
	do {                                                                \
		if (!cunit_check_uint16_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                              \
		}                                                               \
	} while (0)

#define cunit_check_uint32(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), __cond, __VA_ARGS__)
#define cunit_assert_uint32(__l, __r, __cond, ...)                \
	do {                                                          \
		if (!cunit_check_uint32(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint32_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_uint32_equal(__l, __r, ...)                \
	do {                                                        \
		if (!cunit_check_uint32_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_uint32_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_uint32_not_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_uint32_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_uint32_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_uint32_less(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_uint32_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_uint32_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_uint32_less_equal(__l, __r, ...)                \
	do {                                                             \
		if (!cunit_check_uint32_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                           \
		}                                                            \
	} while (0)
#define cunit_check_uint32_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_uint32_greater(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_uint32_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint32_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_uint32_greater_equal(__l, __r, ...)                \
	do {                                                                \
		if (!cunit_check_uint32_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                              \
		}                                                               \
	} while (0)

#define cunit_check_uint64(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), __cond, __VA_ARGS__)
#define cunit_assert_uint64(__l, __r, __cond, ...)                \
	do {                                                          \
		if (!cunit_check_uint64(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint64_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_uint64_equal(__l, __r, ...)                \
	do {                                                        \
		if (!cunit_check_uint64_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_uint64_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_uint64_not_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_uint64_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_uint64_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_uint64_less(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_uint64_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_uint64_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_uint64_less_equal(__l, __r, ...)                \
	do {                                                             \
		if (!cunit_check_uint64_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                           \
		}                                                            \
	} while (0)
#define cunit_check_uint64_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_uint64_greater(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_uint64_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_uint64_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_uint64_greater_equal(__l, __r, ...)                \
	do {                                                                \
		if (!cunit_check_uint64_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                              \
		}                                                               \
	} while (0)

#define cunit_check_float(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), __cond, __VA_ARGS__)
#define cunit_assert_float(__l, __r, __cond, ...)                \
	do {                                                         \
		if (!cunit_check_float(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_float_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_float_equal(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_float_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_float_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_float_not_equal(__l, __r, ...)                \
	do {                                                           \
		if (!cunit_check_float_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                         \
		}                                                          \
	} while (0)
#define cunit_check_float_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_float_less(__l, __r, ...)                \
	do {                                                      \
		if (!cunit_check_float_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                    \
		}                                                     \
	} while (0)
#define cunit_check_float_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_float_less_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_float_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_float_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_float_greater(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_float_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)
#define cunit_check_float_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_float_greater_equal(__l, __r, ...)                \
	do {                                                               \
		if (!cunit_check_float_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                             \
		}                                                              \
	} while (0)

#define cunit_check_double(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), __cond, __VA_ARGS__)
#define cunit_assert_double(__l, __r, __cond, ...)                \
	do {                                                          \
		if (!cunit_check_double(__l, __r, __cond, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_double_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_double_equal(__l, __r, ...)                \
	do {                                                        \
		if (!cunit_check_double_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                      \
		}                                                       \
	} while (0)
#define cunit_check_double_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_double_not_equal(__l, __r, ...)                \
	do {                                                            \
		if (!cunit_check_double_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)
#define cunit_check_double_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_Less, __VA_ARGS__)
#define cunit_assert_double_less(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_double_less(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)
#define cunit_check_double_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_LessEqual, __VA_ARGS__)
#define cunit_assert_double_less_equal(__l, __r, ...)                \
	do {                                                             \
		if (!cunit_check_double_less_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                           \
		}                                                            \
	} while (0)
#define cunit_check_double_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_Greater, __VA_ARGS__)
#define cunit_assert_double_greater(__l, __r, ...)                \
	do {                                                          \
		if (!cunit_check_double_greater(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                        \
		}                                                         \
	} while (0)
#define cunit_check_double_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_assert_double_greater_equal(__l, __r, ...)                \
	do {                                                                \
		if (!cunit_check_double_greater_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                              \
		}                                                               \
	} while (0)

#define cunit_check_pointer_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_POINTER(__l), CUNIT_ANY_POINTER(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_assert_pointer_equal(__l, __r, ...)                \
	do {                                                         \
		if (!cunit_check_pointer_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                       \
		}                                                        \
	} while (0)

#define cunit_check_pointer_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_POINTER(__l), CUNIT_ANY_POINTER(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_assert_pointer_not_equal(__l, __r, ...)                \
	do {                                                             \
		if (!cunit_check_pointer_not_equal(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                           \
		}                                                            \
	} while (0)

#define cunit_check_string(__l, __r, ...) \
	__cunit_check_string(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), STR_NULL __VA_ARGS__)
#define cunit_assert_string(__l, __r, ...)                \
	do {                                                  \
		if (!cunit_check_string(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                \
		}                                                 \
	} while (0)

#define cunit_check_string_n(__l, __r, __size, ...)                                                    \
	__cunit_check_string_n(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), (size_t)(__size), \
						   STR_NULL __VA_ARGS__)
#define cunit_assert_string_n(__l, __r, __size, ...)                \
	do {                                                            \
		if (!cunit_check_string_n(__l, __r, __size, __VA_ARGS__)) { \
			cunit_fatal();                                          \
		}                                                           \
	} while (0)

#define cunit_check_string_case(__l, __r, ...) \
	__cunit_check_string_case(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), STR_NULL __VA_ARGS__)
#define cunit_assert_string_case(__l, __r, ...)                \
	do {                                                       \
		if (!cunit_check_string_case(__l, __r, __VA_ARGS__)) { \
			cunit_fatal();                                     \
		}                                                      \
	} while (0)

#define cunit_check_string_hex(__l, __r, __size, ...)                                                          \
	__cunit_check_string_hex(CUNIT_CTX_CURR, (const uint8_t *)(__l), (const uint8_t *)(__r), (size_t)(__size), \
							 STR_NULL __VA_ARGS__)
#define cunit_assert_string_hex(__l, __r, __size, ...)                \
	do {                                                              \
		if (!cunit_check_string_hex(__l, __r, __size, __VA_ARGS__)) { \
			cunit_fatal();                                            \
		}                                                             \
	} while (0)

#define cunit_check_null(__p, ...) __cunit_check_null(CUNIT_CTX_CURR, (const void *)(__p), STR_NULL __VA_ARGS__)
#define cunit_assert_null(__p, ...)                \
	do {                                           \
		if (!cunit_check_null(__p, __VA_ARGS__)) { \
			cunit_fatal();                         \
		}                                          \
	} while (0)

#define cunit_check_not_null(__p, ...) __cunit_check_not_null(CUNIT_CTX_CURR, (const void *)(__p), STR_NULL __VA_ARGS__)
#define cunit_assert_not_null(__p, ...)                \
	do {                                               \
		if (!cunit_check_not_null(__p, __VA_ARGS__)) { \
			cunit_fatal();                             \
		}                                              \
	} while (0)

#define cunit_check_in_array(__v, __type, __array, __size, ...)                                         \
	__cunit_check_any_in_array(CUNIT_CTX_CURR, CUNIT_ANY_SPECIFY(__v, __type), (const void *)(__array), \
							   (size_t)(__size), STR_NULL __VA_ARGS__)
#define cunit_assert_in_array(__v, __type, __array, __size, ...)                \
	do {                                                                        \
		if (!cunit_check_in_array(__v, __type, __array, __size, __VA_ARGS__)) { \
			cunit_fatal();                                                      \
		}                                                                       \
	} while (0)

#define cunit_check_not_in_array(__v, __type, __array, __size, ...)                                         \
	__cunit_check_any_not_in_array(CUNIT_CTX_CURR, CUNIT_ANY_SPECIFY(__v, __type), (const void *)(__array), \
								   (size_t)(__size), STR_NULL __VA_ARGS__)
#define cunit_assert_not_in_array(__v, __type, __array, __size, ...)                \
	do {                                                                            \
		if (!cunit_check_not_in_array(__v, __type, __array, __size, __VA_ARGS__)) { \
			cunit_fatal();                                                          \
		}                                                                           \
	} while (0)

#else

#define ___cunit_assert_check(__func, ...) \
	do {                                   \
		if (!__func(__VA_ARGS__)) {        \
			cunit_fatal();                 \
		}                                  \
	} while (0)

#define ___cunit_check_compare(__l, __r, __cond, ...) \
	__cunit_check_any_compare(CUNIT_CTX_CURR, (__l), (__r), (__cond), __VA_ARGS__)

#define ___cunit_check_bool(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_BOOL(__l), CUNIT_ANY_BOOL(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_check_bool(...)  ___cunit_check_bool(__VA_ARGS__, STR_NULL)
#define cunit_assert_bool(...) ___cunit_assert_check(cunit_check_bool, __VA_ARGS__)

#define ___cunit_check_true(__v, ...) \
	___cunit_check_compare(CUNIT_ANY_BOOL(__v), CUNIT_ANY_BOOL(true), CUnit_Equal, __VA_ARGS__)
#define cunit_check_true(...)  ___cunit_check_true(__VA_ARGS__, STR_NULL)
#define cunit_assert_true(...) ___cunit_assert_check(cunit_check_true, __VA_ARGS__)

#define ___cunit_check_false(__v, ...) \
	___cunit_check_compare(CUNIT_ANY_BOOL(__v), CUNIT_ANY_BOOL(false), CUnit_Equal, __VA_ARGS__)
#define cunit_check_false(...)  ___cunit_check_false(__VA_ARGS__, STR_NULL)
#define cunit_assert_false(...) ___cunit_assert_check(cunit_check_false, __VA_ARGS__)

#define ___cunit_check_char(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_CHAR(__l), CUNIT_ANY_CHAR(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_check_char(...)  ___cunit_check_char(__VA_ARGS__, STR_NULL)
#define cunit_assert_char(...) ___cunit_assert_check(cunit_check_char, __VA_ARGS__)

#define ___cunit_check_int(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), __cond, __VA_ARGS__)
#define ___cunit_check_int_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_int_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_int_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_int_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_int_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_int_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT(__l), CUNIT_ANY_INT(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_int(...)                ___cunit_check_int(__VA_ARGS__, STR_NULL)
#define cunit_assert_int(...)               ___cunit_assert_check(cunit_check_int, __VA_ARGS__)
#define cunit_check_int_equal(...)          ___cunit_check_int_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int_equal(...)         ___cunit_assert_check(cunit_check_int_equal, __VA_ARGS__)
#define cunit_check_int_not_equal(...)      ___cunit_check_int_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int_not_equal(...)     ___cunit_assert_check(cunit_check_int_not_equal, __VA_ARGS__)
#define cunit_check_int_less(...)           ___cunit_check_int_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_int_less(...)          ___cunit_assert_check(cunit_check_int_less, __VA_ARGS__)
#define cunit_check_int_less_equal(...)     ___cunit_check_int_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int_less_equal(...)    ___cunit_assert_check(cunit_check_int_less_equal, __VA_ARGS__)
#define cunit_check_int_greater(...)        ___cunit_check_int_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_int_greater(...)       ___cunit_assert_check(cunit_check_int_greater, __VA_ARGS__)
#define cunit_check_int_greater_equal(...)  ___cunit_check_int_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int_greater_equal(...) ___cunit_assert_check(cunit_check_int_greater_equal, __VA_ARGS__)

#define ___cunit_check_int8(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), __cond, __VA_ARGS__)
#define ___cunit_check_int8_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_int8_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_int8_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_int8_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_int8_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_int8_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT8(__l), CUNIT_ANY_INT8(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_int8(...)                ___cunit_check_int8(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8(...)               ___cunit_assert_check(cunit_check_int8, __VA_ARGS__)
#define cunit_check_int8_equal(...)          ___cunit_check_int8_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8_equal(...)         ___cunit_assert_check(cunit_check_int8_equal, __VA_ARGS__)
#define cunit_check_int8_not_equal(...)      ___cunit_check_int8_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8_not_equal(...)     ___cunit_assert_check(cunit_check_int8_not_equal, __VA_ARGS__)
#define cunit_check_int8_less(...)           ___cunit_check_int8_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8_less(...)          ___cunit_assert_check(cunit_check_int8_less, __VA_ARGS__)
#define cunit_check_int8_less_equal(...)     ___cunit_check_int8_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8_less_equal(...)    ___cunit_assert_check(cunit_check_int8_less_equal, __VA_ARGS__)
#define cunit_check_int8_greater(...)        ___cunit_check_int8_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8_greater(...)       ___cunit_assert_check(cunit_check_int8_greater, __VA_ARGS__)
#define cunit_check_int8_greater_equal(...)  ___cunit_check_int8_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int8_greater_equal(...) ___cunit_assert_check(cunit_check_int8_greater_equal, __VA_ARGS__)

#define ___cunit_check_int16(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), __cond, __VA_ARGS__)
#define ___cunit_check_int16_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_int16_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_int16_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_int16_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_int16_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_int16_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT16(__l), CUNIT_ANY_INT16(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_int16(...)                ___cunit_check_int16(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16(...)               ___cunit_assert_check(cunit_check_int16, __VA_ARGS__)
#define cunit_check_int16_equal(...)          ___cunit_check_int16_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16_equal(...)         ___cunit_assert_check(cunit_check_int16_equal, __VA_ARGS__)
#define cunit_check_int16_not_equal(...)      ___cunit_check_int16_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16_not_equal(...)     ___cunit_assert_check(cunit_check_int16_not_equal, __VA_ARGS__)
#define cunit_check_int16_less(...)           ___cunit_check_int16_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16_less(...)          ___cunit_assert_check(cunit_check_int16_less, __VA_ARGS__)
#define cunit_check_int16_less_equal(...)     ___cunit_check_int16_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16_less_equal(...)    ___cunit_assert_check(cunit_check_int16_less_equal, __VA_ARGS__)
#define cunit_check_int16_greater(...)        ___cunit_check_int16_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16_greater(...)       ___cunit_assert_check(cunit_check_int16_greater, __VA_ARGS__)
#define cunit_check_int16_greater_equal(...)  ___cunit_check_int16_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int16_greater_equal(...) ___cunit_assert_check(cunit_check_int16_greater_equal, __VA_ARGS__)

#define ___cunit_check_int32(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), __cond, __VA_ARGS__)
#define ___cunit_check_int32_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_int32_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_int32_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_int32_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_int32_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_int32_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT32(__l), CUNIT_ANY_INT32(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_int32(...)                ___cunit_check_int32(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32(...)               ___cunit_assert_check(cunit_check_int32, __VA_ARGS__)
#define cunit_check_int32_equal(...)          ___cunit_check_int32_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32_equal(...)         ___cunit_assert_check(cunit_check_int32_equal, __VA_ARGS__)
#define cunit_check_int32_not_equal(...)      ___cunit_check_int32_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32_not_equal(...)     ___cunit_assert_check(cunit_check_int32_not_equal, __VA_ARGS__)
#define cunit_check_int32_less(...)           ___cunit_check_int32_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32_less(...)          ___cunit_assert_check(cunit_check_int32_less, __VA_ARGS__)
#define cunit_check_int32_less_equal(...)     ___cunit_check_int32_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32_less_equal(...)    ___cunit_assert_check(cunit_check_int32_less_equal, __VA_ARGS__)
#define cunit_check_int32_greater(...)        ___cunit_check_int32_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32_greater(...)       ___cunit_assert_check(cunit_check_int32_greater, __VA_ARGS__)
#define cunit_check_int32_greater_equal(...)  ___cunit_check_int32_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int32_greater_equal(...) ___cunit_assert_check(cunit_check_int32_greater_equal, __VA_ARGS__)

#define ___cunit_check_int64(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), __cond, __VA_ARGS__)
#define ___cunit_check_int64_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_int64_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_int64_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_int64_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_int64_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_int64_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_INT64(__l), CUNIT_ANY_INT64(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_int64(...)                ___cunit_check_int64(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64(...)               ___cunit_assert_check(cunit_check_int64, __VA_ARGS__)
#define cunit_check_int64_equal(...)          ___cunit_check_int64_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64_equal(...)         ___cunit_assert_check(cunit_check_int64_equal, __VA_ARGS__)
#define cunit_check_int64_not_equal(...)      ___cunit_check_int64_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64_not_equal(...)     ___cunit_assert_check(cunit_check_int64_not_equal, __VA_ARGS__)
#define cunit_check_int64_less(...)           ___cunit_check_int64_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64_less(...)          ___cunit_assert_check(cunit_check_int64_less, __VA_ARGS__)
#define cunit_check_int64_less_equal(...)     ___cunit_check_int64_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64_less_equal(...)    ___cunit_assert_check(cunit_check_int64_less_equal, __VA_ARGS__)
#define cunit_check_int64_greater(...)        ___cunit_check_int64_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64_greater(...)       ___cunit_assert_check(cunit_check_int64_greater, __VA_ARGS__)
#define cunit_check_int64_greater_equal(...)  ___cunit_check_int64_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_int64_greater_equal(...) ___cunit_assert_check(cunit_check_int64_greater_equal, __VA_ARGS__)

#define ___cunit_check_uint(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), __cond, __VA_ARGS__)
#define ___cunit_check_uint_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_uint_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_uint_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_uint_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_uint_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_uint_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT(__l), CUNIT_ANY_UINT(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_uint(...)                ___cunit_check_uint(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint(...)               ___cunit_assert_check(cunit_check_uint, __VA_ARGS__)
#define cunit_check_uint_equal(...)          ___cunit_check_uint_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint_equal(...)         ___cunit_assert_check(cunit_check_uint_equal, __VA_ARGS__)
#define cunit_check_uint_not_equal(...)      ___cunit_check_uint_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint_not_equal(...)     ___cunit_assert_check(cunit_check_uint_not_equal, __VA_ARGS__)
#define cunit_check_uint_less(...)           ___cunit_check_uint_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint_less(...)          ___cunit_assert_check(cunit_check_uint_less, __VA_ARGS__)
#define cunit_check_uint_less_equal(...)     ___cunit_check_uint_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint_less_equal(...)    ___cunit_assert_check(cunit_check_uint_less_equal, __VA_ARGS__)
#define cunit_check_uint_greater(...)        ___cunit_check_uint_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint_greater(...)       ___cunit_assert_check(cunit_check_uint_greater, __VA_ARGS__)
#define cunit_check_uint_greater_equal(...)  ___cunit_check_uint_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint_greater_equal(...) ___cunit_assert_check(cunit_check_uint_greater_equal, __VA_ARGS__)

#define ___cunit_check_uint8(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), __cond, __VA_ARGS__)
#define ___cunit_check_uint8_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_uint8_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_uint8_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_uint8_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_uint8_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_uint8_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT8(__l), CUNIT_ANY_UINT8(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_uint8(...)                ___cunit_check_uint8(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8(...)               ___cunit_assert_check(cunit_check_uint8, __VA_ARGS__)
#define cunit_check_uint8_equal(...)          ___cunit_check_uint8_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8_equal(...)         ___cunit_assert_check(cunit_check_uint8_equal, __VA_ARGS__)
#define cunit_check_uint8_not_equal(...)      ___cunit_check_uint8_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8_not_equal(...)     ___cunit_assert_check(cunit_check_uint8_not_equal, __VA_ARGS__)
#define cunit_check_uint8_less(...)           ___cunit_check_uint8_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8_less(...)          ___cunit_assert_check(cunit_check_uint8_less, __VA_ARGS__)
#define cunit_check_uint8_less_equal(...)     ___cunit_check_uint8_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8_less_equal(...)    ___cunit_assert_check(cunit_check_uint8_less_equal, __VA_ARGS__)
#define cunit_check_uint8_greater(...)        ___cunit_check_uint8_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8_greater(...)       ___cunit_assert_check(cunit_check_uint8_greater, __VA_ARGS__)
#define cunit_check_uint8_greater_equal(...)  ___cunit_check_uint8_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint8_greater_equal(...) ___cunit_assert_check(cunit_check_uint8_greater_equal, __VA_ARGS__)

#define ___cunit_check_uint16(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), __cond, __VA_ARGS__)
#define ___cunit_check_uint16_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_uint16_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_uint16_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_uint16_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_uint16_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_uint16_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT16(__l), CUNIT_ANY_UINT16(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_uint16(...)                ___cunit_check_uint16(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16(...)               ___cunit_assert_check(cunit_check_uint16, __VA_ARGS__)
#define cunit_check_uint16_equal(...)          ___cunit_check_uint16_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16_equal(...)         ___cunit_assert_check(cunit_check_uint16_equal, __VA_ARGS__)
#define cunit_check_uint16_not_equal(...)      ___cunit_check_uint16_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16_not_equal(...)     ___cunit_assert_check(cunit_check_uint16_not_equal, __VA_ARGS__)
#define cunit_check_uint16_less(...)           ___cunit_check_uint16_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16_less(...)          ___cunit_assert_check(cunit_check_uint16_less, __VA_ARGS__)
#define cunit_check_uint16_less_equal(...)     ___cunit_check_uint16_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16_less_equal(...)    ___cunit_assert_check(cunit_check_uint16_less_equal, __VA_ARGS__)
#define cunit_check_uint16_greater(...)        ___cunit_check_uint16_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16_greater(...)       ___cunit_assert_check(cunit_check_uint16_greater, __VA_ARGS__)
#define cunit_check_uint16_greater_equal(...)  ___cunit_check_uint16_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint16_greater_equal(...) ___cunit_assert_check(cunit_check_uint16_greater_equal, __VA_ARGS__)

#define ___cunit_check_uint32(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), __cond, __VA_ARGS__)
#define ___cunit_check_uint32_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_uint32_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_uint32_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_uint32_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_uint32_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_uint32_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT32(__l), CUNIT_ANY_UINT32(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_uint32(...)                ___cunit_check_uint32(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32(...)               ___cunit_assert_check(cunit_check_uint32, __VA_ARGS__)
#define cunit_check_uint32_equal(...)          ___cunit_check_uint32_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32_equal(...)         ___cunit_assert_check(cunit_check_uint32_equal, __VA_ARGS__)
#define cunit_check_uint32_not_equal(...)      ___cunit_check_uint32_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32_not_equal(...)     ___cunit_assert_check(cunit_check_uint32_not_equal, __VA_ARGS__)
#define cunit_check_uint32_less(...)           ___cunit_check_uint32_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32_less(...)          ___cunit_assert_check(cunit_check_uint32_less, __VA_ARGS__)
#define cunit_check_uint32_less_equal(...)     ___cunit_check_uint32_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32_less_equal(...)    ___cunit_assert_check(cunit_check_uint32_less_equal, __VA_ARGS__)
#define cunit_check_uint32_greater(...)        ___cunit_check_uint32_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32_greater(...)       ___cunit_assert_check(cunit_check_uint32_greater, __VA_ARGS__)
#define cunit_check_uint32_greater_equal(...)  ___cunit_check_uint32_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint32_greater_equal(...) ___cunit_assert_check(cunit_check_uint32_greater_equal, __VA_ARGS__)

#define ___cunit_check_uint64(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), __cond, __VA_ARGS__)
#define ___cunit_check_uint64_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_uint64_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_uint64_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_uint64_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_uint64_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_uint64_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_UINT64(__l), CUNIT_ANY_UINT64(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_uint64(...)                ___cunit_check_uint64(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64(...)               ___cunit_assert_check(cunit_check_uint64, __VA_ARGS__)
#define cunit_check_uint64_equal(...)          ___cunit_check_uint64_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64_equal(...)         ___cunit_assert_check(cunit_check_uint64_equal, __VA_ARGS__)
#define cunit_check_uint64_not_equal(...)      ___cunit_check_uint64_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64_not_equal(...)     ___cunit_assert_check(cunit_check_uint64_not_equal, __VA_ARGS__)
#define cunit_check_uint64_less(...)           ___cunit_check_uint64_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64_less(...)          ___cunit_assert_check(cunit_check_uint64_less, __VA_ARGS__)
#define cunit_check_uint64_less_equal(...)     ___cunit_check_uint64_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64_less_equal(...)    ___cunit_assert_check(cunit_check_uint64_less_equal, __VA_ARGS__)
#define cunit_check_uint64_greater(...)        ___cunit_check_uint64_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64_greater(...)       ___cunit_assert_check(cunit_check_uint64_greater, __VA_ARGS__)
#define cunit_check_uint64_greater_equal(...)  ___cunit_check_uint64_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_uint64_greater_equal(...) ___cunit_assert_check(cunit_check_uint64_greater_equal, __VA_ARGS__)

#define ___cunit_check_float(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), __cond, __VA_ARGS__)
#define ___cunit_check_float_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_float_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_float_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_float_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_float_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_float_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_FLOAT(__l), CUNIT_ANY_FLOAT(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_float(...)                ___cunit_check_float(__VA_ARGS__, STR_NULL)
#define cunit_assert_float(...)               ___cunit_assert_check(cunit_check_float, __VA_ARGS__)
#define cunit_check_float_equal(...)          ___cunit_check_float_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_float_equal(...)         ___cunit_assert_check(cunit_check_float_equal, __VA_ARGS__)
#define cunit_check_float_not_equal(...)      ___cunit_check_float_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_float_not_equal(...)     ___cunit_assert_check(cunit_check_float_not_equal, __VA_ARGS__)
#define cunit_check_float_less(...)           ___cunit_check_float_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_float_less(...)          ___cunit_assert_check(cunit_check_float_less, __VA_ARGS__)
#define cunit_check_float_less_equal(...)     ___cunit_check_float_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_float_less_equal(...)    ___cunit_assert_check(cunit_check_float_less_equal, __VA_ARGS__)
#define cunit_check_float_greater(...)        ___cunit_check_float_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_float_greater(...)       ___cunit_assert_check(cunit_check_float_greater, __VA_ARGS__)
#define cunit_check_float_greater_equal(...)  ___cunit_check_float_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_float_greater_equal(...) ___cunit_assert_check(cunit_check_float_greater_equal, __VA_ARGS__)

#define ___cunit_check_double(__l, __r, __cond, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), __cond, __VA_ARGS__)
#define ___cunit_check_double_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_Equal, __VA_ARGS__)
#define ___cunit_check_double_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_NotEqual, __VA_ARGS__)
#define ___cunit_check_double_less(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_Less, __VA_ARGS__)
#define ___cunit_check_double_less_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_LessEqual, __VA_ARGS__)
#define ___cunit_check_double_greater(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_Greater, __VA_ARGS__)
#define ___cunit_check_double_greater_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_DOUBLE(__l), CUNIT_ANY_DOUBLE(__r), CUnit_GreaterEqual, __VA_ARGS__)
#define cunit_check_double(...)                ___cunit_check_double(__VA_ARGS__, STR_NULL)
#define cunit_assert_double(...)               ___cunit_assert_check(cunit_check_double, __VA_ARGS__)
#define cunit_check_double_equal(...)          ___cunit_check_double_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_double_equal(...)         ___cunit_assert_check(cunit_check_double_equal, __VA_ARGS__)
#define cunit_check_double_not_equal(...)      ___cunit_check_double_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_double_not_equal(...)     ___cunit_assert_check(cunit_check_double_not_equal, __VA_ARGS__)
#define cunit_check_double_less(...)           ___cunit_check_double_less(__VA_ARGS__, STR_NULL)
#define cunit_assert_double_less(...)          ___cunit_assert_check(cunit_check_double_less, __VA_ARGS__)
#define cunit_check_double_less_equal(...)     ___cunit_check_double_less_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_double_less_equal(...)    ___cunit_assert_check(cunit_check_double_less_equal, __VA_ARGS__)
#define cunit_check_double_greater(...)        ___cunit_check_double_greater(__VA_ARGS__, STR_NULL)
#define cunit_assert_double_greater(...)       ___cunit_assert_check(cunit_check_double_greater, __VA_ARGS__)
#define cunit_check_double_greater_equal(...)  ___cunit_check_double_greater_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_double_greater_equal(...) ___cunit_assert_check(cunit_check_double_greater_equal, __VA_ARGS__)

#define ___cunit_check_pointer_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_POINTER(__l), CUNIT_ANY_POINTER(__r), CUnit_Equal, __VA_ARGS__)
#define cunit_check_pointer_equal(...)  ___cunit_check_pointer_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_pointer_equal(...) ___cunit_assert_check(cunit_check_pointer_equal, __VA_ARGS__)

#define ___cunit_check_pointer_not_equal(__l, __r, ...) \
	___cunit_check_compare(CUNIT_ANY_POINTER(__l), CUNIT_ANY_POINTER(__r), CUnit_NotEqual, __VA_ARGS__)
#define cunit_check_pointer_not_equal(...)  ___cunit_check_pointer_not_equal(__VA_ARGS__, STR_NULL)
#define cunit_assert_pointer_not_equal(...) ___cunit_assert_check(cunit_check_pointer_not_equal, __VA_ARGS__)

#define ___cunit_check_string(__l, __r, ...) \
	__cunit_check_string(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), __VA_ARGS__)
#define cunit_check_string(...)  ___cunit_check_string(__VA_ARGS__, STR_NULL)
#define cunit_assert_string(...) ___cunit_assert_check(cunit_check_string, __VA_ARGS__)

#define ___cunit_check_string_n(__l, __r, __size, ...) \
	__cunit_check_string_n(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), (size_t)(__size), __VA_ARGS__)
#define cunit_check_string_n(...)  ___cunit_check_string_n(__VA_ARGS__, STR_NULL)
#define cunit_assert_string_n(...) ___cunit_assert_check(cunit_check_string_n, __VA_ARGS__)

#define ___cunit_check_string_case(__l, __r, ...) \
	__cunit_check_string_case(CUNIT_CTX_CURR, (const char *)(__l), (const char *)(__r), __VA_ARGS__)
#define cunit_check_string_case(...)  ___cunit_check_string_case(__VA_ARGS__, STR_NULL)
#define cunit_assert_string_case(...) ___cunit_assert_check(cunit_check_string_case, __VA_ARGS__)

#define ___cunit_check_string_hex(__l, __r, __size, ...)                                                       \
	__cunit_check_string_hex(CUNIT_CTX_CURR, (const uint8_t *)(__l), (const uint8_t *)(__r), (size_t)(__size), \
							 STR_NULL __VA_ARGS__)
#define cunit_check_string_hex(...)  ___cunit_check_string_hex(__VA_ARGS__, STR_NULL)
#define cunit_assert_string_hex(...) ___cunit_assert_check(cunit_check_string_hex, __VA_ARGS__)

#define ___cunit_check_null(__p, ...) __cunit_check_null(CUNIT_CTX_CURR, (const void *)(__p), __VA_ARGS__)
#define cunit_check_null(...)         ___cunit_check_null(__VA_ARGS__, STR_NULL)
#define cunit_assert_null(...)        ___cunit_assert_check(cunit_check_null, __VA_ARGS__)

#define ___cunit_check_not_null(__p, ...) __cunit_check_not_null(CUNIT_CTX_CURR, (const void *)(__p), __VA_ARGS__)
#define cunit_check_not_null(...)         ___cunit_check_not_null(__VA_ARGS__, STR_NULL)
#define cunit_assert_not_null(...)        ___cunit_assert_check(cunit_check_not_null, __VA_ARGS__)

#define ___cunit_check_in_array(__v, __type, __array, __size, ...)                                      \
	__cunit_check_any_in_array(CUNIT_CTX_CURR, CUNIT_ANY_SPECIFY(__v, __type), (const void *)(__array), \
							   (size_t)(__size), STR_NULL __VA_ARGS__)
#define cunit_check_in_array(...)  ___cunit_check_in_array(__VA_ARGS__, STR_NULL)
#define cunit_assert_in_array(...) ___cunit_assert_check(cunit_check_in_array, __VA_ARGS__)

#define ___cunit_check_not_in_array(__v, __type, __array, __size, ...)                                      \
	__cunit_check_any_not_in_array(CUNIT_CTX_CURR, CUNIT_ANY_SPECIFY(__v, __type), (const void *)(__array), \
								   (size_t)(__size), STR_NULL __VA_ARGS__)
#define cunit_check_not_in_array(...)  ___cunit_check_not_in_array(__VA_ARGS__, STR_NULL)
#define cunit_assert_not_in_array(...) ___cunit_assert_check(cunit_check_not_in_array, __VA_ARGS__)

#endif

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

#define assert_bool  cunit_assert_bool
#define assert_true  cunit_assert_true
#define assert_false cunit_assert_false

#define check_bool  cunit_check_bool
#define check_true  cunit_check_true
#define check_false cunit_check_false

#define assert_char cunit_assert_char
#define check_char  cunit_check_char

#define assert_int_eq cunit_assert_int_equal
#define assert_int_ne cunit_assert_int_not_equal
#define assert_int_lt cunit_assert_int_less
#define assert_int_le cunit_assert_int_less_equal
#define assert_int_gt cunit_assert_int_greater
#define assert_int_ge cunit_assert_int_greater_equal

#define check_int_eq cunit_check_int_equal
#define check_int_ne cunit_check_int_not_equal
#define check_int_lt cunit_check_int_less
#define check_int_le cunit_check_int_less_equal
#define check_int_gt cunit_check_int_greater
#define check_int_ge cunit_check_int_greater_equal

#define assert_int8_eq cunit_assert_int8_equal
#define assert_int8_ne cunit_assert_int8_not_equal
#define assert_int8_lt cunit_assert_int8_less
#define assert_int8_le cunit_assert_int8_less_equal
#define assert_int8_gt cunit_assert_int8_greater
#define assert_int8_ge cunit_assert_int8_greater_equal

#define check_int8_eq cunit_check_int8_equal
#define check_int8_ne cunit_check_int8_not_equal
#define check_int8_lt cunit_check_int8_less
#define check_int8_le cunit_check_int8_less_equal
#define check_int8_gt cunit_check_int8_greater
#define check_int8_ge cunit_check_int8_greater_equal

#define assert_int16_eq cunit_assert_int16_equal
#define assert_int16_ne cunit_assert_int16_not_equal
#define assert_int16_lt cunit_assert_int16_less
#define assert_int16_le cunit_assert_int16_less_equal
#define assert_int16_gt cunit_assert_int16_greater
#define assert_int16_ge cunit_assert_int16_greater_equal

#define check_int16_eq cunit_check_int16_equal
#define check_int16_ne cunit_check_int16_not_equal
#define check_int16_lt cunit_check_int16_less
#define check_int16_le cunit_check_int16_less_equal
#define check_int16_gt cunit_check_int16_greater
#define check_int16_ge cunit_check_int16_greater_equal

#define assert_int32_eq cunit_assert_int32_equal
#define assert_int32_ne cunit_assert_int32_not_equal
#define assert_int32_lt cunit_assert_int32_less
#define assert_int32_le cunit_assert_int32_less_equal
#define assert_int32_gt cunit_assert_int32_greater
#define assert_int32_ge cunit_assert_int32_greater_equal

#define check_int32_eq cunit_check_int32_equal
#define check_int32_ne cunit_check_int32_not_equal
#define check_int32_lt cunit_check_int32_less
#define check_int32_le cunit_check_int32_less_equal
#define check_int32_gt cunit_check_int32_greater
#define check_int32_ge cunit_check_int32_greater_equal

#define assert_int64_eq cunit_assert_int64_equal
#define assert_int64_ne cunit_assert_int64_not_equal
#define assert_int64_lt cunit_assert_int64_less
#define assert_int64_le cunit_assert_int64_less_equal
#define assert_int64_gt cunit_assert_int64_greater
#define assert_int64_ge cunit_assert_int64_greater_equal

#define check_int64_eq cunit_check_int64_equal
#define check_int64_ne cunit_check_int64_not_equal
#define check_int64_lt cunit_check_int64_less
#define check_int64_le cunit_check_int64_less_equal
#define check_int64_gt cunit_check_int64_greater
#define check_int64_ge cunit_check_int64_greater_equal

#define assert_uint_eq cunit_assert_uint_equal
#define assert_uint_ne cunit_assert_uint_not_equal
#define assert_uint_lt cunit_assert_uint_less
#define assert_uint_le cunit_assert_uint_less_equal
#define assert_uint_gt cunit_assert_uint_greater
#define assert_uint_ge cunit_assert_uint_greater_equal

#define check_uint_eq cunit_check_uint_equal
#define check_uint_ne cunit_check_uint_not_equal
#define check_uint_lt cunit_check_uint_less
#define check_uint_le cunit_check_uint_less_equal
#define check_uint_gt cunit_check_uint_greater
#define check_uint_ge cunit_check_uint_greater_equal

#define assert_uint8_eq cunit_assert_uint8_equal
#define assert_uint8_ne cunit_assert_uint8_not_equal
#define assert_uint8_lt cunit_assert_uint8_less
#define assert_uint8_le cunit_assert_uint8_less_equal
#define assert_uint8_gt cunit_assert_uint8_greater
#define assert_uint8_ge cunit_assert_uint8_greater_equal

#define check_uint8_eq cunit_check_uint8_equal
#define check_uint8_ne cunit_check_uint8_not_equal
#define check_uint8_lt cunit_check_uint8_less
#define check_uint8_le cunit_check_uint8_less_equal
#define check_uint8_gt cunit_check_uint8_greater
#define check_uint8_ge cunit_check_uint8_greater_equal

#define assert_uint16_eq cunit_assert_uint16_equal
#define assert_uint16_ne cunit_assert_uint16_not_equal
#define assert_uint16_lt cunit_assert_uint16_less
#define assert_uint16_le cunit_assert_uint16_less_equal
#define assert_uint16_gt cunit_assert_uint16_greater
#define assert_uint16_ge cunit_assert_uint16_greater_equal

#define check_uint16_eq cunit_check_uint16_equal
#define check_uint16_ne cunit_check_uint16_not_equal
#define check_uint16_lt cunit_check_uint16_less
#define check_uint16_le cunit_check_uint16_less_equal
#define check_uint16_gt cunit_check_uint16_greater
#define check_uint16_ge cunit_check_uint16_greater_equal

#define assert_uint32_eq cunit_assert_uint32_equal
#define assert_uint32_ne cunit_assert_uint32_not_equal
#define assert_uint32_lt cunit_assert_uint32_less
#define assert_uint32_le cunit_assert_uint32_less_equal
#define assert_uint32_gt cunit_assert_uint32_greater
#define assert_uint32_ge cunit_assert_uint32_greater_equal

#define check_uint32_eq cunit_check_uint32_equal
#define check_uint32_ne cunit_check_uint32_not_equal
#define check_uint32_lt cunit_check_uint32_less
#define check_uint32_le cunit_check_uint32_less_equal
#define check_uint32_gt cunit_check_uint32_greater
#define check_uint32_ge cunit_check_uint32_greater_equal

#define assert_uint64_eq cunit_assert_uint64_equal
#define assert_uint64_ne cunit_assert_uint64_not_equal
#define assert_uint64_lt cunit_assert_uint64_less
#define assert_uint64_le cunit_assert_uint64_less_equal
#define assert_uint64_gt cunit_assert_uint64_greater
#define assert_uint64_ge cunit_assert_uint64_greater_equal

#define check_uint64_eq cunit_check_uint64_equal
#define check_uint64_ne cunit_check_uint64_not_equal
#define check_uint64_lt cunit_check_uint64_less
#define check_uint64_le cunit_check_uint64_less_equal
#define check_uint64_gt cunit_check_uint64_greater
#define check_uint64_ge cunit_check_uint64_greater_equal

#define assert_float_eq cunit_assert_float_equal
#define assert_float_ne cunit_assert_float_not_equal
#define assert_float_lt cunit_assert_float_less
#define assert_float_le cunit_assert_float_less_equal
#define assert_float_gt cunit_assert_float_greater
#define assert_float_ge cunit_assert_float_greater_equal

#define check_float_eq cunit_check_float_equal
#define check_float_ne cunit_check_float_not_equal
#define check_float_lt cunit_check_float_less
#define check_float_le cunit_check_float_less_equal
#define check_float_gt cunit_check_float_greater
#define check_float_ge cunit_check_float_greater_equal

#define assert_float32_eq cunit_assert_float_equal
#define assert_float32_ne cunit_assert_float_not_equal
#define assert_float32_lt cunit_assert_float_less
#define assert_float32_le cunit_assert_float_less_equal
#define assert_float32_gt cunit_assert_float_greater
#define assert_float32_ge cunit_assert_float_greater_equal

#define check_float32_eq cunit_check_float_equal
#define check_float32_ne cunit_check_float_not_equal
#define check_float32_lt cunit_check_float_less
#define check_float32_le cunit_check_float_less_equal
#define check_float32_gt cunit_check_float_greater
#define check_float32_ge cunit_check_float_greater_equal

#define assert_double_eq cunit_assert_double_equal
#define assert_double_ne cunit_assert_double_not_equal
#define assert_double_lt cunit_assert_double_less
#define assert_double_le cunit_assert_double_less_equal
#define assert_double_gt cunit_assert_double_greater
#define assert_double_ge cunit_assert_double_greater_equal

#define check_double_eq cunit_check_double_equal
#define check_double_ne cunit_check_double_not_equal
#define check_double_lt cunit_check_double_less
#define check_double_le cunit_check_double_less_equal
#define check_double_gt cunit_check_double_greater
#define check_double_ge cunit_check_double_greater_equal

#define assert_float64_eq cunit_assert_double_equal
#define assert_float64_ne cunit_assert_double_not_equal
#define assert_float64_lt cunit_assert_double_less
#define assert_float64_le cunit_assert_double_less_equal
#define assert_float64_gt cunit_assert_double_greater
#define assert_float64_ge cunit_assert_double_greater_equal

#define check_float64_eq cunit_check_double_equal
#define check_float64_ne cunit_check_double_not_equal
#define check_float64_lt cunit_check_double_less
#define check_float64_le cunit_check_double_less_equal
#define check_float64_gt cunit_check_double_greater
#define check_float64_ge cunit_check_double_greater_equal

#define assert_pointer_eq cunit_assert_pointer_equal
#define assert_pointer_ne cunit_assert_pointer_not_equal

#define check_pointer_eq cunit_check_pointer_equal
#define check_pointer_ne cunit_check_pointer_not_equal

#define assert_null     cunit_assert_null
#define assert_not_null cunit_assert_not_null

#define check_null     cunit_check_null
#define check_not_null cunit_check_not_null

#define assert_string      cunit_assert_string
#define assert_string_n    cunit_assert_string_n
#define assert_string_case cunit_assert_string_case
#define assert_string_hex  cunit_assert_string_hex

#define check_string      cunit_check_string
#define check_string_n    cunit_check_string_n
#define check_string_case cunit_check_string_case
#define check_string_hex  cunit_check_string_hex

#define assert_in_array     cunit_assert_in_array
#define assert_not_in_array cunit_assert_not_in_array

#define check_in_array     cunit_check_in_array
#define check_not_in_array cunit_check_not_in_array

// -------------------------[cunit private functions]-------------------------

const char *__cunit_relative(const char *abs_path);
void        __cunit_pass(const cunit_context_t ctx);
void        __cunit_fatal(const cunit_context_t ctx);
bool        __cunit_check_string(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...);
bool __cunit_check_string_n(const cunit_context_t ctx, const char *l, const char *r, size_t size, const char *format,
							...);
bool __cunit_check_string_case(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...);
bool __cunit_check_string_hex(const cunit_context_t ctx, const uint8_t *l, const uint8_t *r, size_t size,
							  const char *format, ...);
bool __cunit_check_null(const cunit_context_t ctx, const void *p, const char *format, ...);
bool __cunit_check_not_null(const cunit_context_t ctx, const void *p, const char *format, ...);
bool __cunit_check_any_compare(const cunit_context_t ctx, const cunit_any_t l, const cunit_any_t r, int cond,
							   const char *format, ...);
bool __cunit_check_any_in_array(const cunit_context_t ctx, const cunit_any_t var, const void *array, size_t size,
								const char *format, ...);
bool __cunit_check_any_not_in_array(const cunit_context_t ctx, const cunit_any_t var, const void *array, size_t size,
									const char *format, ...);

#ifdef __cplusplus
}
#endif
#endif  // CUNIT_H
