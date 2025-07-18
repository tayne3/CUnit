#include "cunit.h"

void test_assertions(void) {
	check_false(true);
	assert_not_null(NULL);
}

int main(void) {
	cunit_init();

	CUNIT_SUITE_BEGIN("Assertion Tests", NULL, NULL)
	CUNIT_TEST("All Assertions", test_assertions)
	CUNIT_SUITE_END()

	return cunit_run();
}
