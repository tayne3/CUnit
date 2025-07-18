#include "cunit.h"

void test_assertions(void) {
	check_false(true);
	assert_not_null(NULL);
}

int main(void) {
	cunit_init();

	cunit_add_test_suite("Assertion Tests", NULL, NULL);
	cunit_add_test("All Assertions", test_assertions);

	return cunit_run();
}
