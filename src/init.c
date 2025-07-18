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

#include "init.h"

#ifndef CUNIT_ROOT_PATH
#error "CUNIT_ROOT_PATH not defined"
#endif
#ifndef CUNIT_BUILD_PATH
#error "CUNIT_BUILD_PATH not defined"
#endif

#ifdef _MSC_VER
#define __cunit_separator '\\'
#else
#define __cunit_separator '/'
#endif

#ifdef _WIN32
#define __cunit_is_drive_letter(path) \
	(((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z')) && (path[1] == ':') && (path[2] == '\\' || path[2] == '/'))
#define __cunit_is_unc_path(path)      ((path[0] == '\\' && path[1] == '\\') || (path[0] == '/' && path[1] == '/'))
#define __cunit_is_absolute_path(path) (__cunit_is_drive_letter(path) || __cunit_is_unc_path(path))
#else
#define __cunit_is_absolute_path(path) (path[0] == '/')
#endif

#define cunit_root_path    CUNIT_ROOT_PATH
#define cunit_root_length  (sizeof(cunit_root_path) - 1)
#define cunit_build_path   CUNIT_BUILD_PATH
#define cunit_build_length (sizeof(cunit_build_path) - 1)

static int __cunit_build_level = -1;

void __cunit_relative_initialization(void) {
	if (STR_ISEMPTY(cunit_root_path) || cunit_build_length < cunit_root_length || strncmp(cunit_build_path, cunit_root_path, cunit_root_length) != 0) {
		return;
	}

	int         build_level = 0, dot_count = 0;
	const char *p = (const char *)cunit_build_path + cunit_root_length;
	for (char c = *p; build_level >= 0 && c != '\0'; c = *p) {
		if (c == __cunit_separator) {
			if (dot_count == 2) { build_level--; }
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
			if (*p == '\0') { break; }
			build_level++;
			dot_count = 0;
			p++;
			continue;
		}
	}

	__cunit_build_level = build_level >= 0 ? build_level : -1;
}

static const char *__cunit_absolute_clip(const char *abs) {
	for (size_t i = 0; i < cunit_root_length; i++) {
		if (abs[i] != cunit_root_path[i]) { return abs; }
	}
	const char *relative = abs + cunit_root_length;
	for (; *relative == __cunit_separator;) { relative++; }
	return relative;
}

static const char *__cunit_relative_clip(const char *rel) {
	if (__cunit_build_level == -1) { __cunit_init(); }

	const char *p         = rel;
	int         dot_count = 0, dir_level = __cunit_build_level;
	for (char c = *p; dir_level > 0 && c != '\0'; c = *p) {
		if (c == __cunit_separator) {
			if (dot_count == 2) { dir_level--; }
			dot_count = 0;
			p++;
			continue;
		} else if (c == '.') {
			dot_count++;
			p++;
		} else {
			for (; *p != __cunit_separator; p++) {
				if (*p == '\0') { break; }
			}
			if (*p == '\0') { break; }
			dir_level++;
			dot_count = 0;
			p++;
			continue;
		}
	}

	return dir_level == 0 ? p : rel;
}

const char *__cunit_relative(const char *src_path) {
	return !src_path ? "(nil)" : __cunit_is_absolute_path(src_path) ? __cunit_absolute_clip(src_path) : __cunit_relative_clip(src_path);
}
