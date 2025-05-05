#include "cunit.h"

int main(void) {
	check_false(true);
	assert_not_null(NULL);

	cunit_pass();
}
