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
#ifndef CUNIT_VALUE_H
#define CUNIT_VALUE_H

#include "def.h"

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

#endif  // CUNIT_VALUE_H
