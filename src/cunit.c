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
#include "cunit.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>

// -------------------------[STATIC DECLARATION]-------------------------

#ifdef CUNIT_ROOT_PATH
#define cunit_root_path CUNIT_ROOT_PATH
#else
#define cunit_root_path STR_NULL
#endif

// comparison results: greater than, less than, and equal to
enum cunit_compare_result {
	CUnitCompare_Unknown = -2,
	CUnitCompare_Less    = -1,
	CUnitCompare_Equal   = 0,
	CUnitCompare_Greater = 1
};

#define CUNIT_COMPARE_RESULT_TO_STR(x) \
	((x) == CUnitCompare_Less ? "<" : (x) == CUnitCompare_Equal ? "=" : (x) == CUnitCompare_Greater ? ">" : "?")

#define __cunit_print_check(ctx) printf("\033[33;2m%s:%d CHECK \033[0m", __cunit_relative(ctx.file), ctx.line)

#define __cunit_print_info(format)                                                   \
	do {                                                                             \
		if (!STR_ISEMPTY(format)) {                                                  \
			printf("\033[37;2m%s:%d \033[0m", __cunit_relative(ctx.file), ctx.line); \
			va_list args;                                                            \
			va_start(args, format);                                                  \
			vprintf(format, args);                                                   \
			va_end(args);                                                            \
		}                                                                            \
	} while (0)

#define CUNIT_STRCMP(l, r)        (l == r ? 0 : !l ? -1 : !r ? 1 : strcmp(l, r))
#define CUNIT_STRNCMP(l, r, size) (l == r ? 0 : !l ? -1 : !r ? 1 : strncmp(l, r, size))

/**
 * Compare the contents of two byte arrays
 * @param l Left byte array
 * @param r Right byte array
 * @param size Size of the byte arrays
 * @return Returns -1 if l is less than r, 1 if l is greater than r, otherwise returns 0
 */
static inline int __cunit_bytearray_compare(const uint8_t *l, const uint8_t *r, size_t size);

/**
 * Check if a variable is in an array
 * @param var The variable to check
 * @param array The array
 * @param size Size of the array
 * @return Returns true if the variable is in the array, otherwise returns false
 */
static inline bool __cunit_check_any_is_in_array(const cunit_any_t var, const void *array, size_t size);

/**
 * Print a hexadecimal array
 * @param array The array to print
 * @param length Length of the array
 */
static inline void __cunit_print_hex(const uint8_t *array, size_t length);

// -------------------------[GLOBAL DEFINITION]-------------------------

const char *__cunit_relative(const char *abs_path) {
	if (STR_ISEMPTY(abs_path)) {
		return "(nil)";
	}
	if (STR_ISEMPTY(cunit_root_path)) {
		return abs_path;
	}

	for (size_t i = 0; i < sizeof(cunit_root_path) - 1; i++) {
		if (abs_path[i] != cunit_root_path[i]) {
			return abs_path;  // Return original path if not matched
		}
	}

	// Remove prefix
	const char *relative = abs_path + sizeof(cunit_root_path) - 1;
	// Remove separators
	for (; *relative == '\\' || *relative == '/';) {
		relative++;
	}
	return relative;
}

void __cunit_pass(const cunit_context_t ctx) {
	printf("\033[32;2m%s:%d \033[0m", __cunit_relative(ctx.file), ctx.line);
	printf("test passed!" STR_NEWLINE);
	exit(EXIT_SUCCESS);
}

void __cunit_fatal(const cunit_context_t ctx) {
	printf("\033[31;2m%s:%d \033[0m", __cunit_relative(ctx.file), ctx.line);
	printf("test failed!" STR_NEWLINE);
	exit(EXIT_FAILURE);
}

void cunit_any_print(const cunit_any_t *self) {
	switch (self->type) {
		case CUnitType_Bool: printf("%s", (self->d.b) ? "true" : "false"); break;
		case CUnitType_Char: printf("%c", self->d.c); break;
		case CUnitType_Float32: printf("%f", self->d.f32); break;
		case CUnitType_Float64: printf("%f", self->d.f64); break;
		case CUnitType_String: printf("%s", self->d.str); break;
		case CUnitType_Pointer: printf("%p", self->d.ptr); break;
		case CUnitType_Int: printf("%d", self->d.i); break;
		case CUnitType_Int8: printf("%" PRIi8, self->d.i8); break;
		case CUnitType_Int16: printf("%" PRIi16, self->d.i16); break;
		case CUnitType_Int32: printf("%" PRIi32, self->d.i32); break;
		case CUnitType_Int64: printf("%" PRIi64, self->d.i64); break;
		case CUnitType_Uint: printf("%u", self->d.u); break;
		case CUnitType_Uint8: printf("%" PRIu8, self->d.u8); break;
		case CUnitType_Uint16: printf("%" PRIu16, self->d.u16); break;
		case CUnitType_Uint32: printf("%" PRIu32, self->d.u32); break;
		case CUnitType_Uint64: printf("%" PRIu64, self->d.u64); break;
		case CUnitType_Invalid:
		default: printf("%s", "(invalid)"); break;
	}
}

int cunit_any_compare(const cunit_any_t *l, const cunit_any_t *r) {
	if (l->type != r->type) {
		return -2;
	}
	switch (l->type) {
		case CUnitType_Bool: return (l->d.b > r->d.b) - (l->d.b < r->d.b);
		case CUnitType_Char: return (l->d.c > r->d.c) - (l->d.c < r->d.c);
		case CUnitType_Float32:
			return isnan(l->d.f32) ? isnan(r->d.f32) ? 0 : -1 :
				   isnan(r->d.f32) ? 1 :
									 (l->d.f32 > r->d.f32) - (l->d.f32 < r->d.f32);
		case CUnitType_Float64:
			return isnan(l->d.f64) ? isnan(r->d.f64) ? 0 : -1 :
				   isnan(r->d.f64) ? 1 :
									 (l->d.f64 > r->d.f64) - (l->d.f64 < r->d.f64);
		case CUnitType_String: return CUNIT_STRCMP(l->d.str, r->d.str);
		case CUnitType_Pointer: return (l->d.ptr > r->d.ptr) - (l->d.ptr < r->d.ptr);
		case CUnitType_Int: return (l->d.i > r->d.i) - (l->d.i < r->d.i);
		case CUnitType_Int8: return (l->d.i8 > r->d.i8) - (l->d.i8 < r->d.i8);
		case CUnitType_Int16: return (l->d.i16 > r->d.i16) - (l->d.i16 < r->d.i16);
		case CUnitType_Int32: return (l->d.i32 > r->d.i32) - (l->d.i32 < r->d.i32);
		case CUnitType_Int64: return (l->d.i64 > r->d.i64) - (l->d.i64 < r->d.i64);
		case CUnitType_Uint: return (l->d.u > r->d.u) - (l->d.u < r->d.u);
		case CUnitType_Uint8: return (l->d.u8 > r->d.u8) - (l->d.u8 < r->d.u8);
		case CUnitType_Uint16: return (l->d.u16 > r->d.u16) - (l->d.u16 < r->d.u16);
		case CUnitType_Uint32: return (l->d.u32 > r->d.u32) - (l->d.u32 < r->d.u32);
		case CUnitType_Uint64: return (l->d.u64 > r->d.u64) - (l->d.u64 < r->d.u64);
		case CUnitType_Invalid:
		default: return -2;
	}
}

void cunit_any_swap(cunit_any_t *l, cunit_any_t *r) {
	l->d.u64 ^= r->d.u64;
	r->d.u64 ^= l->d.u64;
	l->d.u64 ^= r->d.u64;
	l->type ^= r->type;
	r->type ^= l->type;
	l->type ^= r->type;
}

bool __cunit_check_hex(const cunit_context_t ctx, const uint8_t *l, const uint8_t *r, size_t size, const char *format,
					   ...) {
	if (l == r) {
		return true;
	}
	if (l && r && !__cunit_bytearray_compare(l, r, size)) {
		return true;
	}

	__cunit_print_check(ctx);
	printf("`");
	__cunit_print_hex(l, size);
	printf("` != `");
	__cunit_print_hex(r, size);
	printf("` " STR_NEWLINE);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_string(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...) {
	if (l == r) {
		return true;
	}
	if (l && r && !CUNIT_STRCMP(l, r)) {
		return true;
	}

	__cunit_print_check(ctx);
	printf("%s != %s" STR_NEWLINE, l, r);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_string_n(const cunit_context_t ctx, const char *l, const char *r, size_t size, const char *format,
							...) {
	if (l == r) {
		return true;
	}
	if (l && r && !CUNIT_STRNCMP(l, r, size)) {
		return true;
	}

	__cunit_print_check(ctx);
	printf("%s != %s" STR_NEWLINE, l, r);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_null(const cunit_context_t ctx, const void *p, const char *format, ...) {
	if (!p) {
		return true;
	}

	__cunit_print_check(ctx);
	printf("%p is not null" STR_NEWLINE, p);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_not_null(const cunit_context_t ctx, const void *p, const char *format, ...) {
	if (p) {
		return true;
	}

	__cunit_print_check(ctx);
	printf("(null) is null" STR_NEWLINE);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_any_compare(const cunit_context_t ctx, const cunit_any_t l, const cunit_any_t r, int cond,
							   const char *format, ...) {
	const enum cunit_compare_result ret = cunit_any_compare(&l, &r);

	switch (ret) {
		case CUnitCompare_Less:
			if (cond & CUnit_Less) {
				return true;
			}
			break;
		case CUnitCompare_Equal:
			if (cond & CUnit_Equal) {
				return true;
			}
			break;
		case CUnitCompare_Greater:
			if (cond & CUnit_Greater) {
				return true;
			}
			break;
		default: break;
	}

	__cunit_print_check(ctx);
	cunit_any_print(&l);
	printf(" %s ", CUNIT_COMPARE_RESULT_TO_STR(ret));
	cunit_any_print(&r);
	printf(STR_NEWLINE);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_any_in_array(const cunit_context_t ctx, const cunit_any_t var, const void *array, size_t size,
								const char *format, ...) {
	if (__cunit_check_any_is_in_array(var, array, size)) {
		return true;
	}

	__cunit_print_check(ctx);
	cunit_any_print(&var);
	printf(" is not in array" STR_NEWLINE);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_any_not_in_array(const cunit_context_t ctx, const cunit_any_t var, const void *array, size_t size,
									const char *format, ...) {
	if (!__cunit_check_any_is_in_array(var, array, size)) {
		return true;
	}

	__cunit_print_check(ctx);
	cunit_any_print(&var);
	printf(" is in array" STR_NEWLINE);

	__cunit_print_info(format);
	return false;
}

bool __cunit_check_ret(const cunit_context_t ctx, int ret, const char *format, ...) {
	if (ret == 0) {
		return true;
	}

	__cunit_print_check(ctx);
	printf("return value is %d" STR_NEWLINE, ret);

	__cunit_print_info(format);
	return false;
}

// -------------------------[STATIC DEFINITION]-------------------------

static inline int __cunit_bytearray_compare(const uint8_t *l, const uint8_t *r, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (l[i] != r[i]) {
			return (l[i] > r[i]) - (l[i] < r[i]);
		}
	}
	return 0;
}

static inline bool __cunit_check_any_is_in_array(const cunit_any_t var, const void *array, size_t size) {
	switch (var.type) {
		case CUnitType_Bool:
			for (size_t i = 0; i < size; i++) {
				if (((const bool *)array)[i] == var.d.b) {
					return true;
				}
			}
			return false;
		case CUnitType_Char:
			for (size_t i = 0; i < size; i++) {
				if (((const char *)array)[i] == var.d.c) {
					return true;
				}
			}
			return false;
		case CUnitType_Int:
			for (size_t i = 0; i < size; i++) {
				if (((const int *)array)[i] == var.d.i) {
					return true;
				}
			}
			return false;
		case CUnitType_Int8:
			for (size_t i = 0; i < size; i++) {
				if (((const int8_t *)array)[i] == var.d.i8) {
					return true;
				}
			}
			return false;
		case CUnitType_Int16:
			for (size_t i = 0; i < size; i++) {
				if (((const int16_t *)array)[i] == var.d.i16) {
					return true;
				}
			}
			return false;
		case CUnitType_Int32:
			for (size_t i = 0; i < size; i++) {
				if (((const int32_t *)array)[i] == var.d.i32) {
					return true;
				}
			}
			return false;
		case CUnitType_Int64:
			for (size_t i = 0; i < size; i++) {
				if (((const int64_t *)array)[i] == var.d.i64) {
					return true;
				}
			}
			return false;
		case CUnitType_Uint:
			for (size_t i = 0; i < size; i++) {
				if (((const unsigned int *)array)[i] == var.d.u) {
					return true;
				}
			}
			return false;
		case CUnitType_Uint8:
			for (size_t i = 0; i < size; i++) {
				if (((const uint8_t *)array)[i] == var.d.u8) {
					return true;
				}
			}
			return false;
		case CUnitType_Uint16:
			for (size_t i = 0; i < size; i++) {
				if (((const uint16_t *)array)[i] == var.d.u16) {
					return true;
				}
			}
			return false;
		case CUnitType_Uint32:
			for (size_t i = 0; i < size; i++) {
				if (((const uint32_t *)array)[i] == var.d.u32) {
					return true;
				}
			}
			return false;
		case CUnitType_Uint64:
			for (size_t i = 0; i < size; i++) {
				if (((const uint64_t *)array)[i] == var.d.u64) {
					return true;
				}
			}
			return false;
		case CUnitType_Float32:
			for (size_t i = 0; i < size; i++) {
				const float value = ((const float *)array)[i];
				if (isnan(value)) {
					if (isnan(var.d.f32)) {
						return true;
					}
					continue;
				}
				if (value == var.d.f32) {
					return true;
				}
			}
			return false;
		case CUnitType_Float64:
			for (size_t i = 0; i < size; i++) {
				const double value = ((const double *)array)[i];
				if (isnan(value)) {
					if (isnan(var.d.f64)) {
						return true;
					}
					continue;
				}
				if (value == var.d.f64) {
					return true;
				}
			}
			return false;
		case CUnitType_String:
			for (size_t i = 0; i < size; i++) {
				if (((const char *const *)array)[i] == var.d.str ||
					CUNIT_STRCMP(((const char *const *)array)[i], var.d.str) == 0) {
					return true;
				}
			}
			return false;
		case CUnitType_Pointer:
			for (size_t i = 0; i < size; i++) {
				if (((const void *const *)array)[i] == var.d.ptr) {
					return true;
				}
			}
			return false;
		default: return true;
	}
}

static inline void __cunit_print_hex(const uint8_t *array, size_t length) {
	if (!array) {
		printf("(null)");
		return;
	}

	for (;;) {
		if (--length > 0) {
			printf("%02X ", *array++);
			continue;
		}
		if (length == 0) {
			printf("%02X", *array++);
		}
		break;
	}
}
