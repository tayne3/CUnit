#include "cunit.h"

int main(void) {
	assert_bool(true, true);
	assert_bool(false, false);
	assert_true(1 > 0);
	assert_false(0 > 1);
	assert_char('a', 'a');

	assert_int_eq(0, 0);
	assert_int8_lt(1, 2);
	assert_int16_gt(1, 0);
	assert_int32_le(1, 2);
	assert_int64_ge(0, 0);

	assert_int_eq(INT_MAX, INT_MAX);
	assert_int8_eq(INT8_MAX, INT8_MAX);
	assert_int16_eq(INT16_MAX, INT16_MAX);
	assert_int32_eq(INT32_MAX, INT32_MAX);
	assert_int64_eq(INT64_MAX, INT64_MAX);

	assert_int_ne(INT_MAX, INT_MIN);
	assert_int8_ne(INT8_MAX, INT8_MIN);
	assert_int16_ne(INT16_MAX, INT16_MIN);
	assert_int32_ne(INT32_MAX, INT32_MIN);
	assert_int64_ne(INT64_MAX, INT64_MIN);

	assert_int_lt(INT_MIN, INT_MAX);
	assert_int8_lt(INT8_MIN, INT8_MAX);
	assert_int16_lt(INT16_MIN, INT16_MAX);
	assert_int32_lt(INT32_MIN, INT32_MAX);
	assert_int64_lt(INT64_MIN, INT64_MAX);

	assert_int_le(INT_MIN, INT_MAX);
	assert_int8_le(INT8_MIN, INT8_MAX);
	assert_int16_le(INT16_MIN, INT16_MAX);
	assert_int32_le(INT32_MIN, INT32_MAX);
	assert_int64_le(INT64_MIN, INT64_MAX);

	assert_int_gt(INT_MAX, INT_MIN);
	assert_int8_gt(INT8_MAX, INT8_MIN);
	assert_int16_gt(INT16_MAX, INT16_MIN);
	assert_int32_gt(INT32_MAX, INT32_MIN);
	assert_int64_gt(INT64_MAX, INT64_MIN);

	assert_int_ge(INT_MAX, INT_MAX);
	assert_int8_ge(INT8_MAX, INT8_MAX);
	assert_int16_ge(INT16_MAX, INT16_MAX);
	assert_int32_ge(INT32_MAX, INT32_MAX);
	assert_int64_ge(INT64_MAX, INT64_MAX);

	assert_uint_ge(1, 0);
	assert_uint8_ge(1, 0);
	assert_uint16_ge(1, 0);
	assert_uint32_ge(1, 0);
	assert_uint64_ge(1, 0);

	assert_uint_eq(UINT_MAX, UINT_MAX);
	assert_uint8_eq(UINT8_MAX, UINT8_MAX);
	assert_uint16_eq(UINT16_MAX, UINT16_MAX);
	assert_uint32_eq(UINT32_MAX, UINT32_MAX);
	assert_uint64_eq(UINT64_MAX, UINT64_MAX);

	assert_uint_ne(UINT_MAX, 0);
	assert_uint8_ne(UINT8_MAX, 0);
	assert_uint16_ne(UINT16_MAX, 0);
	assert_uint32_ne(UINT32_MAX, 0);
	assert_uint64_ne(UINT64_MAX, 0);

	assert_uint_lt(0, UINT_MAX);
	assert_uint8_lt(0, UINT8_MAX);
	assert_uint16_lt(0, UINT16_MAX);
	assert_uint32_lt(0, UINT32_MAX);
	assert_uint64_lt(0, UINT64_MAX);

	assert_uint_le(0, UINT_MAX);
	assert_uint8_le(0, UINT8_MAX);
	assert_uint16_le(0, UINT16_MAX);
	assert_uint32_le(0, UINT32_MAX);
	assert_uint64_le(0, UINT64_MAX);

	assert_uint_gt(UINT_MAX, 0);
	assert_uint8_gt(UINT8_MAX, 0);
	assert_uint16_gt(UINT16_MAX, 0);
	assert_uint32_gt(UINT32_MAX, 0);
	assert_uint64_gt(UINT64_MAX, 0);

	assert_uint_ge(UINT_MAX, UINT_MAX);
	assert_uint8_ge(UINT8_MAX, UINT8_MAX);
	assert_uint16_ge(UINT16_MAX, UINT16_MAX);
	assert_uint32_ge(UINT32_MAX, UINT32_MAX);
	assert_uint64_ge(UINT64_MAX, UINT64_MAX);

	assert_float32_ge(9.9f, 3.4f);
	assert_float32_lt(NAN, 0.0f);
	assert_float32_le(NAN, 0.0f);
	assert_float32_gt(0.0f, NAN);
	assert_float32_ge(0.0f, NAN);
	assert_float32_ne(NAN, 0.0f);
	assert_float32_eq(NAN, 0.0f * NAN);

	assert_float32_eq(123.009f, 123.009f);
	assert_float32_ne(123.009f, 123.010f);
	assert_float32_lt(123.009f, 123.010f);
	assert_float32_le(123.009f, 123.010f);
	assert_float32_gt(123.010f, 123.009f);
	assert_float32_ge(123.010f, 123.009f);

	assert_float64_ge(1.10, 0.04);
	assert_float64_lt(NAN, 0.0);
	assert_float64_le(NAN, 0.0);
	assert_float64_gt(0.0, NAN);
	assert_float64_ge(0.0, NAN);
	assert_float64_ne(NAN, 0.0);
	assert_float64_eq(NAN, 0.0 * NAN);

	assert_float64_eq(123456.78900001, 123456.78900001);
	assert_float64_ne(123456.78900001, 123456.78900000);
	assert_float64_lt(123456.78900000, 123456.78900001);
	assert_float64_le(123456.78900000, 123456.78900001);
	assert_float64_gt(123456.78900001, 123456.78900000);
	assert_float64_ge(123456.78900001, 123456.78900000);

	const char *strnull = STR_NULL;
	assert_ptr_eq(strnull, strnull);
	assert_ptr_ne(NULL, strnull);
	assert_null(NULL);
	assert_not_null(strnull);

	assert_str_eq("Hello", "Hello");
	assert_str_n("HelloWorld", "Hello", 5);
	assert_str_case("HellO", "hEllo");
	assert_str_hex("HelloWorld", "Hello", 5);

	cunit_println("cunit_print...");

	check_bool(true, false, "check bool: true != false");
	check_false(0 == 0, "check true: 0 == 0");
	check_true(0 != 0, "check true: 0 != 0");

	if (check_bool(true, true)) { cunit_println("check bool: true == true"); }
	if (!check_bool(true, false)) { cunit_println("check bool: true != false"); }

	check_char('a', 'b', "check char: 'a' != 'b'");

	if (check_char('a', 'a')) { cunit_println("check char: 'a' == 'a'"); }

	check_int_eq(0, 0);
	check_int_eq(0, -1);

	assert_str_eq(STR_NULL, STR_NULL);
	assert_str_eq("hello world", "hello world");
	assert_str_n("hello world", "hello", 5);
	check_str_eq("hello world", "hello");
	check_str_case("hello world", "Hello");

	{
		const unsigned char hex_1[] = {0x01, 0x02, 0x03, 0x04, 0x05};
		const unsigned char hex_2[] = {0x01, 0x02, 0x03, 0x05, 0x04};

		assert_str_hex(hex_1, hex_2, 1);
		assert_str_hex(hex_1, hex_2, 2);
		assert_str_hex(hex_1, hex_2, 3);

		check_str_hex(hex_1, hex_2, 4);
		check_str_hex(hex_1, hex_2, 5);
	}

	{
		const int    array[]    = {1, 2, 3, 4, 5};
		const size_t array_size = sizeof(array) / sizeof(array[0]);

		assert_not_in_array(CUNIT_VALUE_INT(0), array, array_size);
		assert_in_array(CUNIT_VALUE_INT(1), array, array_size);
		assert_in_array(CUNIT_VALUE_INT(2), array, array_size);
		assert_in_array(CUNIT_VALUE_INT(3), array, array_size);
		assert_in_array(CUNIT_VALUE_INT(4), array, array_size);
		assert_in_array(CUNIT_VALUE_INT(5), array, array_size);
		assert_not_in_array(CUNIT_VALUE_INT(6), array, array_size);

		check_in_array(CUNIT_VALUE_INT(7), array, array_size);
	}

	cunit_pass();
}
