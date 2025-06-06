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

#include <stdarg.h>

// -------------------------[STATIC DECLARATION]-------------------------

#ifdef _MSC_VER
#define strcasecmp  _stricmp
#define strncasecmp _strnicmp
#else
#include <strings.h>
#define stricmp  strcasecmp
#define strnicmp strncasecmp
#endif

#ifdef _MSC_VER
#define __cunit_separator '\\'
#else
#define __cunit_separator '/'
#endif

#ifdef _WIN32
#define __cunit_is_drive_letter(path)                                                                  \
	(((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z')) && (path[1] == ':') && \
	 (path[2] == '\\' || path[2] == '/'))
#define __cunit_is_unc_path(path)      ((path[0] == '\\' && path[1] == '\\') || (path[0] == '/' && path[1] == '/'))
#define __cunit_is_absolute_path(path) (__cunit_is_drive_letter(path) || __cunit_is_unc_path(path))
#else
#define __cunit_is_absolute_path(path) (path[0] == '/')
#endif

#ifdef _WIN32
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#include <windows.h>
typedef INIT_ONCE cunit_once_flag_t;
typedef void (*cunit_once_routine_t)(void);
#define CUNIT_ONCE_FLAG_INIT INIT_ONCE_STATIC_INIT

static BOOL CALLBACK __cunit_once_callback(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *Context) {
	(void)InitOnce;
	(void)Context;
	cunit_once_routine_t routine = (cunit_once_routine_t)Parameter;
	routine();
	return TRUE;
}

static void cunit_call_once(cunit_once_flag_t *flag, cunit_once_routine_t routine) {
	InitOnceExecuteOnce(flag, __cunit_once_callback, (PVOID)routine, NULL);
}
#else
#include <pthread.h>
typedef pthread_once_t cunit_once_flag_t;
typedef void (*cunit_once_routine_t)(void);
#define CUNIT_ONCE_FLAG_INIT PTHREAD_ONCE_INIT

static void cunit_call_once(cunit_once_flag_t *flag, cunit_once_routine_t routine) {
	pthread_once(flag, routine);
}
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

#define __cunit_print_not_expected(ctx) \
	printf("\033[33;2m%s:%d\033[0m not expected: ", __cunit_relative(ctx.file), ctx.line)

#define __cunit_print_info(format)                                                   \
	do {                                                                             \
		if (!STR_ISEMPTY(format)) {                                                  \
			printf("\033[37;2m%s:%d\033[0m ", __cunit_relative(ctx.file), ctx.line); \
			va_list args;                                                            \
			va_start(args, format);                                                  \
			vprintf(format, args);                                                   \
			va_end(args);                                                            \
			fputs(STR_NEWLINE, stdout);                                              \
		}                                                                            \
	} while (0)

#define CUNIT_STRCMP(l, r)        (l == r ? 0 : !l ? -1 : !r ? 1 : strcmp(l, r))
#define CUNIT_STRCASECMP(l, r)    (l == r ? 0 : !l ? -1 : !r ? 1 : strcasecmp(l, r))
#define CUNIT_STRNCMP(l, r, size) (l == r ? 0 : !l ? -1 : !r ? 1 : strncmp(l, r, size))

// Helper for printing uint64_t
static inline void __cunit_print_u64(uint64_t n);
// Helper for printing int64_t
static inline void __cunit_print_i64(int64_t n);
// Helper for printing pointer address in hex
static inline void __cunit_print_ptr(const void *p);

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

#if defined(CUNIT_ROOT_PATH) && defined(CUNIT_BUILD_PATH)

#define cunit_root_path    CUNIT_ROOT_PATH
#define cunit_root_length  (sizeof(cunit_root_path) - 1)
#define cunit_build_path   CUNIT_BUILD_PATH
#define cunit_build_length (sizeof(cunit_build_path) - 1)

static int __cunit_build_level = -1;

/**
 * @brief Initializes the __cunit_build_level.
 * This function calculates the depth of the CMake build directory relative to the project's root directory.
 * The __cunit_build_level represents how many ".." are needed to go from the build directory
 * to the project root directory.
 *
 * For example:
 * CUNIT_ROOT_PATH  = "/project"
 * CUNIT_BUILD_PATH = "/project/build/debug"
 * __cunit_build_level will be 2.
 *
 * CUNIT_ROOT_PATH  = "/project"
 * CUNIT_BUILD_PATH = "/project/build/../build/debug" (equivalent to /project/build/debug)
 * __cunit_build_level will also be 2, as ".." is handled.
 *
 * The function parses the part of cunit_build_path that comes after cunit_root_path.
 * It counts directory levels, decrementing for ".." and incrementing for actual directory names.
 * If cunit_build_path is not a subdirectory of cunit_root_path or is empty,
 * __cunit_build_level remains -1, and path relativization for relative paths might not work as intended.
 */
static void __cunit_relative_initialization(void) {
	if (STR_ISEMPTY(cunit_root_path) || cunit_build_length < cunit_root_length ||
		strncmp(cunit_build_path, cunit_root_path, cunit_root_length) != 0) {
		return;
	}

	int         build_level = 0, dot_count = 0;
	const char *p = (const char *)cunit_build_path + cunit_root_length;
	for (char c = *p; build_level >= 0 && c != '\0'; c = *p) {
		if (c == __cunit_separator) {
			if (dot_count == 2) {
				build_level--;
			}
			dot_count = 0;
			p++;
			continue;
		} else if (c == '.') {
			dot_count++;
			p++;
		} else {
			for (; *p != __cunit_separator; p++) {
				if (*p == '\0') {
					build_level++;
					break;
				}
			}
			if (*p == '\0') {
				break;
			}
			build_level++;
			dot_count = 0;
			p++;
			continue;
		}
	}

	__cunit_build_level = build_level >= 0 ? build_level : -1;
}

/**
 * @brief Clips the CUNIT_ROOT_PATH prefix from an absolute path.
 * If the given absolute path 'abs' starts with CUNIT_ROOT_PATH, this function
 * returns a pointer to the character following the CUNIT_ROOT_PATH prefix and
 * any subsequent path separators.
 *
 * For example:
 * CUNIT_ROOT_PATH = "/project"
 * abs = "/project/src/main.c"
 * Returns a pointer to "src/main.c".
 *
 * If 'abs' does not start with CUNIT_ROOT_PATH, or if CUNIT_ROOT_PATH is not defined/valid,
 * the original 'abs' path is returned.
 *
 * @param abs The absolute path string.
 * @return A pointer to the relativized path segment, or the original path.
 */
static const char *__cunit_absolute_clip(const char *abs) {
	for (size_t i = 0; i < cunit_root_length; i++) {
		if (abs[i] != cunit_root_path[i]) {
			return abs;  // Return original path if not matched
		}
	}
	// Remove prefix
	const char *relative = abs + cunit_root_length;
	// Remove separators
	for (; *relative == __cunit_separator;) {
		relative++;
	}
	return relative;
}

/**
 * @brief Attempts to convert a path relative to the build directory to a path relative to the project root.
 * This function is called when __cunit_relative encounters a relative path.
 * It uses __cunit_build_level (the depth of the build directory relative to the root)
 * to process ".." segments at the beginning of the 'rel' path.
 *
 * The core idea is to "consume" leading ".." segments from 'rel' while decrementing
 * 'dir_level' (initialized from __cunit_build_level).
 * - If 'rel' is "foo/bar.c" and __cunit_build_level is 2 (e.g., build dir is root/build/debug),
 *   'dir_level' starts at 2. The loop for ".." won't run. The `else` branch handles "foo",
 *   increments `dir_level` to 3. Since `dir_level` (3) is not 0, the original 'rel' ("foo/bar.c")
 *   is returned. This path is still effectively relative to the build directory.
 * - If 'rel' is "../../src/main.c" and __cunit_build_level is 2,
 *   'dir_level' starts at 2.
 *   The first ".." in 'rel' reduces 'dir_level' to 1.
 *   The second ".." in 'rel' reduces 'dir_level' to 0.
 *   'p' now points to "src/main.c". Since 'dir_level' is 0, "src/main.c" is returned,
 *   which is correctly relative to the project root.
 *
 * The `dir_level++` for non-"." and non-".." components is crucial. It ensures that if
 * the path does not navigate "upwards" enough with ".." to reach or pass the project root level
 * (i.e., make dir_level zero or negative), the function returns the original relative path
 * (or a partially processed one if some ".." were present). This means
 * the returned path, in such cases, remains relative to the build directory, not the project root.
 *
 * @param rel The path string, assumed to be relative to the build directory.
 * @return A pointer to a path segment. If 'rel' could be fully relativized to the project root
 *         (i.e., dir_level became 0), it points to the part of 'rel' that is relative to root.
 *         Otherwise, it returns 'rel' (or a part of it if some '..' were processed),
 *         which remains relative to the build directory or an intermediate directory.
 */
static const char *__cunit_relative_clip(const char *rel) {
	static cunit_once_flag_t initialization_flag = CUNIT_ONCE_FLAG_INIT;
	cunit_call_once(&initialization_flag, __cunit_relative_initialization);

	const char *p         = rel;
	int         dot_count = 0, dir_level = __cunit_build_level;
	for (char c = *p; dir_level > 0 && c != '\0'; c = *p) {
		if (c == __cunit_separator) {
			if (dot_count == 2) {
				dir_level--;
			}
			dot_count = 0;
			p++;
			continue;
		} else if (c == '.') {
			dot_count++;
			p++;
		} else {
			for (; *p != __cunit_separator; p++) {
				if (*p == '\0') {
					break;
				}
			}
			if (*p == '\0') {
				break;
			}
			dir_level++;
			dot_count = 0;
			p++;
			continue;
		}
	}

	return dir_level == 0 ? p : rel;
}

/**
 * @brief Provides a potentially shortened path string for display, relative to the project root if possible.
 *
 * This function processes `src_path` to make it more concise for output:
 * 1. If `CUNIT_ROOT_PATH` and `CUNIT_BUILD_PATH` are not defined, it returns `src_path` as is (or "(nil)").
 * 2. If `src_path` is an absolute path:
 *    It calls `__cunit_absolute_clip` to remove the `CUNIT_ROOT_PATH` prefix,
 *    if `src_path` is within the project root. Otherwise, returns `src_path`.
 * 3. If `src_path` is a relative path (e.g., from `__FILE__` which is relative to the build dir):
 *    It calls `__cunit_relative_clip`. This attempts to convert the path to be
 *    relative to `CUNIT_ROOT_PATH` by processing leading ".." segments based on the
 *    calculated `__cunit_build_level`.
 *    - If the relative path successfully "ascends" to the project root (e.g., "../../src/file.c"
 *      when build dir is "root/build/debug"), a path like "src/file.c" is returned.
 *    - If the relative path does not ascend to the project root (e.g., "mytest.c" or "subdir/mytest.c"
 *      when build dir is "root/build/debug"), the original (or partially processed) relative path
 *      is returned. This path is then still relative to the build directory.
 *
 * This function operates purely with pointer arithmetic and does not perform memory allocations or
 * create new strings. It returns pointers into the original `src_path` string or static strings.
 *
 * @param src_path The original source path string (e.g., from __FILE__).
 * @return A pointer to a string representing the relativized path, or "(nil)".
 */
const char *__cunit_relative(const char *src_path) {
	return !src_path                          ? "(nil)" :
		   __cunit_is_absolute_path(src_path) ? __cunit_absolute_clip(src_path) :
												__cunit_relative_clip(src_path);
}

#undef cunit_root_path
#undef cunit_root_length
#undef cunit_build_path
#undef cunit_build_length

#else
const char *__cunit_relative(const char *src_path) {
	return !src_path ? "(nil)" : src_path;
}
#endif

void __cunit_pass(const cunit_context_t ctx) {
	printf("\033[32;2m%s:%d\033[0m ", __cunit_relative(ctx.file), ctx.line);
	fputs("test passed!" STR_NEWLINE, stdout);
	exit(EXIT_SUCCESS);
}

void __cunit_fatal(const cunit_context_t ctx) {
	printf("\033[31;2m%s:%d\033[0m ", __cunit_relative(ctx.file), ctx.line);
	fputs("test failed!" STR_NEWLINE, stdout);
	exit(EXIT_FAILURE);
}

void cunit_any_print(const cunit_any_t *self) {
	switch (self->type) {
		case CUnitType_Bool: fputs((self->d.b) ? "true" : "false", stdout); break;
		case CUnitType_Char: putchar(self->d.c); break;
		case CUnitType_Float32: printf("%f", self->d.f32); break;
		case CUnitType_Float64: printf("%f", self->d.f64); break;
		case CUnitType_String: fputs(self->d.str ? self->d.str : "(null)", stdout); break;
		case CUnitType_Pointer: __cunit_print_ptr(self->d.ptr); break;
		case CUnitType_Int: __cunit_print_i64(self->d.i); break;
		case CUnitType_Int8: __cunit_print_i64(self->d.i8); break;
		case CUnitType_Int16: __cunit_print_i64(self->d.i16); break;
		case CUnitType_Int32: __cunit_print_i64(self->d.i32); break;
		case CUnitType_Int64: __cunit_print_i64(self->d.i64); break;
		case CUnitType_Uint: __cunit_print_u64(self->d.u); break;
		case CUnitType_Uint8: __cunit_print_u64(self->d.u8); break;
		case CUnitType_Uint16: __cunit_print_u64(self->d.u16); break;
		case CUnitType_Uint32: __cunit_print_u64(self->d.u32); break;
		case CUnitType_Uint64: __cunit_print_u64(self->d.u64); break;
		case CUnitType_Invalid:
		default: fputs("(invalid)", stdout); break;
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
			// return isnan(l->d.f32)                            ? isnan(r->d.f32) ? 0 : -1 :
			// 	   isnan(r->d.f32)                            ? 1 :
			// 	   (fabsf(l->d.f32 - r->d.f32) < FLT_EPSILON) ? 0 :
			// 													(l->d.f32 > r->d.f32) - (l->d.f32 < r->d.f32);
			return isnan(l->d.f32)                            ? isnan(r->d.f32) ? 0 : -1 :
				   isnan(r->d.f32)                            ? 1 :
																(l->d.f32 > r->d.f32) - (l->d.f32 < r->d.f32);
		case CUnitType_Float64:
			return isnan(l->d.f64)                           ? isnan(r->d.f64) ? 0 : -1 :
				   isnan(r->d.f64)                           ? 1 :
				   (fabs(l->d.f64 - r->d.f64) < DBL_EPSILON) ? 0 :
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

bool __cunit_check_string(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...) {
	if (l == r) {
		return true;
	}
	if (l && r && !CUNIT_STRCMP(l, r)) {
		return true;
	}

	__cunit_print_not_expected(ctx);
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

	__cunit_print_not_expected(ctx);
	printf("%s != %s" STR_NEWLINE, l, r);
	__cunit_print_info(format);
	return false;
}

bool __cunit_check_string_case(const cunit_context_t ctx, const char *l, const char *r, const char *format, ...) {
	if (l == r) {
		return true;
	}
	if (l && r && !CUNIT_STRCASECMP(l, r)) {
		return true;
	}

	__cunit_print_not_expected(ctx);
	printf("%s != %s" STR_NEWLINE, l, r);
	__cunit_print_info(format);
	return false;
}

bool __cunit_check_string_hex(const cunit_context_t ctx, const uint8_t *l, const uint8_t *r, size_t size,
							  const char *format, ...) {
	if (l == r) {
		return true;
	}
	if (l && r && !__cunit_bytearray_compare(l, r, size)) {
		return true;
	}

	__cunit_print_not_expected(ctx);
	fputs("`", stdout);
	__cunit_print_hex(l, size);
	fputs("` != `", stdout);
	__cunit_print_hex(r, size);
	fputs("` " STR_NEWLINE, stdout);
	__cunit_print_info(format);
	return false;
}

bool __cunit_check_null(const cunit_context_t ctx, const void *p, const char *format, ...) {
	if (!p) {
		return true;
	}

	__cunit_print_not_expected(ctx);
	printf("%p is not null" STR_NEWLINE, p);
	__cunit_print_info(format);
	return false;
}

bool __cunit_check_not_null(const cunit_context_t ctx, const void *p, const char *format, ...) {
	if (p) {
		return true;
	}

	__cunit_print_not_expected(ctx);
	fputs("(null) is null" STR_NEWLINE, stdout);
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

	__cunit_print_not_expected(ctx);
	cunit_any_print(&l);
	fputs(" ", stdout);
	fputs(CUNIT_COMPARE_RESULT_TO_STR(ret), stdout);
	fputs(" ", stdout);
	cunit_any_print(&r);
	fputs(STR_NEWLINE, stdout);
	__cunit_print_info(format);
	return false;
}

bool __cunit_check_any_in_array(const cunit_context_t ctx, const cunit_any_t var, const void *array, size_t size,
								const char *format, ...) {
	if (__cunit_check_any_is_in_array(var, array, size)) {
		return true;
	}

	__cunit_print_not_expected(ctx);
	cunit_any_print(&var);
	fputs(" is not in array" STR_NEWLINE, stdout);
	__cunit_print_info(format);
	return false;
}

bool __cunit_check_any_not_in_array(const cunit_context_t ctx, const cunit_any_t var, const void *array, size_t size,
									const char *format, ...) {
	if (!__cunit_check_any_is_in_array(var, array, size)) {
		return true;
	}

	__cunit_print_not_expected(ctx);
	cunit_any_print(&var);
	fputs(" is in array" STR_NEWLINE, stdout);
	__cunit_print_info(format);
	return false;
}

// -------------------------[STATIC DEFINITION]-------------------------

static inline void __cunit_print_u64(uint64_t n) {
	// Buffer large enough for 20 digits of uint64_t + null terminator
	char buf[21];
	int  i = sizeof(buf) - 1;
	buf[i] = '\0';

	if (n == 0) {
		buf[--i] = '0';
	} else {
		while (n > 0) {
			buf[--i] = (n % 10) + '0';
			n /= 10;
		}
	}
	fputs(&buf[i], stdout);
}

static inline void __cunit_print_i64(int64_t n) {
	if (n < 0) {
		putchar('-');
		// Handle INT64_MIN which has no positive equivalent
		if (n == INT64_MIN) {
			fputs("9223372036854775808", stdout);
			return;
		}
		n = -n;  // Make positive
	}
	__cunit_print_u64((uint64_t)n);
}

static inline void __cunit_print_ptr(const void *p) {
	if (p == NULL) {
		// Consistent with typical %p output for NULL
		fputs("(nil)", stdout);
		return;
	}
	// uintptr_t is an integer type wide enough to hold a pointer
	uintptr_t addr = (uintptr_t)p;
	// Buffer: "0x" + 2 hex chars per byte + null terminator
	char  buf[sizeof(uintptr_t) * 2 + 3];
	char *ptr = &buf[sizeof(buf) - 1];
	*ptr      = '\0';

	if (addr == 0) {
		*--ptr = '0';
	} else {
		const char hex_digits[] = "0123456789abcdef";
		while (addr > 0) {
			// Get the last 4 bits and convert to hex char
			*--ptr = hex_digits[addr & 0xF];
			// Shift right by 4 bits
			addr >>= 4;
		}
	}
	*--ptr = 'x';  // Add "0x" prefix
	*--ptr = '0';
	fputs(ptr, stdout);  // Print the resulting hex string
}

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
				if (fabsf(value - var.d.f32) < FLT_EPSILON) {
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
				if (fabs(value - var.d.f64) < DBL_EPSILON) {
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
		fputs("(null)", stdout);
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
