#include "cunit.h"

void test_assertions(void) {
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

    assert_uint_ge(1, 0);
    assert_uint8_ge(1, 0);
    assert_uint16_ge(1, 0);
    assert_uint32_ge(1, 0);
    assert_uint64_ge(1, 0);

    assert_float32_ge(9.9f, 3.4f);
    assert_float64_ge(1.10, 0.04);

    const char *strnull = STR_NULL;
    assert_ptr_eq(strnull, strnull);
    assert_ptr_ne(NULL, strnull);
    assert_null(NULL);
    assert_not_null(strnull);

    assert_str_eq("Hello", "Hello");
    assert_str_n("HelloWorld", "Hello", 5);
    assert_str_case("HellO", "hEllo");
    assert_str_hex("HelloWorld", "Hello", 5);
}

void test_checks(void) {
    check_bool(true, false, "check bool: true != false");
    check_false(0 == 0, "check true: 0 == 0");
    check_true(0 != 0, "check true: 0 != 0");

    if (check_bool(true, true)) {
        cunit_println("check bool: true == true");
    }
    if (!check_bool(true, false)) {
        cunit_println("check bool: true != false");
    }

    check_char('a', 'b', "check char: 'a' != 'b'");

    if (check_char('a', 'a')) {
        cunit_println("check char: 'a' == 'a'");
    }

    check_int_eq(0, 0);
    check_int_eq(0, -1);

    check_str_eq("hello world", "hello");
    check_str_case("hello world", "Hello");

    const unsigned char hex_1[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    const unsigned char hex_2[] = {0x01, 0x02, 0x03, 0x05, 0x04};
    check_str_hex(hex_1, hex_2, 4);

    const int array[] = {1, 2, 3, 4, 5};
    const size_t array_size = sizeof(array) / sizeof(array[0]);
    check_in_array(CUNIT_VALUE_INT(7), array, array_size);
}

int main(void) {
    cunit_init();

	CUNIT_SUITE_BEGIN("Assertion Tests", NULL, NULL)
	CUNIT_TEST("All Assertions", test_assertions)
	CUNIT_SUITE_END()

	CUNIT_SUITE_BEGIN("Check Tests", NULL, NULL)
	CUNIT_TEST("All Checks", test_checks)
	CUNIT_SUITE_END()

    return cunit_run();
}
