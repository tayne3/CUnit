#include "cunit.h"
#include "init.h"
#include "once.h"

// Represents a single test case.
struct cunit_test {
	const char        *name;  // The name of the test.
	cunit_test_func_t  func;  // A pointer to the test function.
	struct cunit_test *next;  // A pointer to the next test in the suite.
};

// Represents a test suite, which is a collection of tests.
struct cunit_test_suite {
	const char              *name;          // The name of the test suite.
	cunit_setup_func_t       setup;         // A pointer to the setup function for the suite.
	cunit_teardown_func_t    teardown;      // A pointer to the teardown function for the suite.
	cunit_test_t            *tests;         // A pointer to the first test in the suite.
	cunit_test_t            *last_test;     // A pointer to the last test in the suite.
	struct cunit_test_suite *next;          // A pointer to the next test suite.
	int                      test_count;    // The number of tests in the suite.
	int                      passed_count;  // The number of passed tests in the suite.
	int                      failed_count;  // The number of failed tests in the suite.
};

// Represents the global registry for all test suites and test results.
typedef struct {
	cunit_test_suite_t *suites;          // A pointer to the first test suite.
	cunit_test_suite_t *current_suite;   // A pointer to the current test suite being added to.
	cunit_test_suite_t *last_suite;      // A pointer to the last test suite in the list.
	int                 total_tests;     // The total number of tests across all suites.
	int                 total_passed;    // The total number of passed tests across all suites.
	int                 total_failed;    // The total number of failed tests across all suites.
	cunit_error_mode_t  error_mode;      // The error handling mode.
	bool                is_initialized;  // A flag indicating whether the registry has been initialized.
	bool                test_running;    // A flag indicating whether a test is currently running.
	bool                test_failed;     // A flag indicating whether the current test has failed.
} cunit_registry_t;

// Initializes a cunit_registry_t struct with default values.
#define CUNIT_REGISTRY_INITIALIZATION               \
	{                                               \
		.suites         = NULL,                     \
		.current_suite  = NULL,                     \
		.last_suite     = NULL,                     \
		.total_tests    = 0,                        \
		.total_passed   = 0,                        \
		.total_failed   = 0,                        \
		.error_mode     = CUNIT_ERROR_MODE_COLLECT, \
		.is_initialized = false,                    \
		.test_running   = false,                    \
		.test_failed    = false,                    \
	}

// The global instance of the test registry.
static cunit_registry_t g_cunit_registry = CUNIT_REGISTRY_INITIALIZATION;

// Runs a single test case.
static void __cunit_run_test(cunit_test_suite_t *suite, cunit_test_t *test) {
	g_cunit_registry.test_failed = false;

	if (suite->setup) { suite->setup(); }

	test->func();

	if (suite->teardown) { suite->teardown(); }

	if (g_cunit_registry.test_failed) {
		suite->failed_count++;
		g_cunit_registry.total_failed++;
		printf("[ \033[31mFAILED\033[0m ] %s\n", test->name);
	} else {
		suite->passed_count++;
		g_cunit_registry.total_passed++;
		printf("[ \033[32mPASSED\033[0m ] %s\n", test->name);
	}
}

// Marks the current test as failed.
static inline void __cunit_test_fail(void) { g_cunit_registry.test_failed = true; }

// Prints the header for a test suite.
static inline void __cunit_print_suite_header(const char *suite_name) { printf("\n\033[33mRunning test suite: %s\033[0m\n", suite_name); }

// Prints the summary for a test suite.
static void __cunit_print_suite_summary(cunit_test_suite_t *suite) {
	printf("\033[33mSuite Summary: %d passed, %d failed, %d total\033[0m\n", suite->passed_count, suite->failed_count, suite->test_count);
}

// Prints the final summary of all test results.
static inline void __cunit_print_final_summary(void) {
	printf("\n\033[33mFinal Summary: %d passed, %d failed, %d total\033[0m\n", g_cunit_registry.total_passed, g_cunit_registry.total_failed,
		   g_cunit_registry.total_tests);
}

// This function is called when a test passes.
void __cunit_pass(const cunit_context_t ctx) {
	if (!g_cunit_registry.test_running) {
		printf("\033[32;2m%s:%d\033[0m ", __cunit_relative(ctx.file), ctx.line);
		fputs("test passed!" STR_NEWLINE, stdout);
		exit(EXIT_SUCCESS);
	}
}

// This function is called when a test fails.
void __cunit_fatal(const cunit_context_t ctx) {
	printf("\033[31;2m%s:%d\033[0m ", __cunit_relative(ctx.file), ctx.line);
	fputs("test failed!" STR_NEWLINE, stdout);
	if (g_cunit_registry.test_running) {
		__cunit_test_fail();
		if (g_cunit_registry.error_mode == CUNIT_ERROR_MODE_FAIL_FAST) { exit(EXIT_FAILURE); }
	} else {
		exit(EXIT_FAILURE);
	}
}

// Initializes the CUnit framework.
void __cunit_init(void) {
	if (g_cunit_registry.is_initialized) { return; }
	__cunit_relative_initialization();
	g_cunit_registry.error_mode     = CUNIT_ERROR_MODE_COLLECT;
	g_cunit_registry.is_initialized = true;
}

// Initializes the CUnit framework using a once-only mechanism.
void cunit_init(void) {
	static cunit_once_flag_t initialization_flag = CUNIT_ONCE_FLAG_INIT;
	cunit_call_once(&initialization_flag, __cunit_init);
}

// Cleans up all resources used by CUnit.
void cunit_cleanup(void) {
	cunit_test_suite_t *suite = g_cunit_registry.suites;
	while (suite) {
		cunit_test_t *test = suite->tests;
		while (test) {
			cunit_test_t *next_test = test->next;
			free(test);
			test = next_test;
		}
		cunit_test_suite_t *next_suite = suite->next;
		free(suite);
		suite = next_suite;
	}
	memset(&g_cunit_registry, 0, sizeof(cunit_registry_t));
}

// Adds a new test suite to the registry.
void cunit_add_test_suite(const char *name, cunit_setup_func_t setup, cunit_teardown_func_t teardown) {
	if (!g_cunit_registry.is_initialized) { cunit_init(); }

	cunit_test_suite_t *suite = (cunit_test_suite_t *)calloc(1, sizeof(cunit_test_suite_t));
	if (!suite) { return; }

	suite->name     = name;
	suite->setup    = setup;
	suite->teardown = teardown;

	if (!g_cunit_registry.suites) {
		g_cunit_registry.suites = suite;
	} else {
		g_cunit_registry.last_suite->next = suite;
	}
	g_cunit_registry.last_suite    = suite;
	g_cunit_registry.current_suite = suite;
}

// Adds a new test to the current test suite.
void cunit_add_test(const char *name, cunit_test_func_t test_func) {
	if (!g_cunit_registry.current_suite) { return; }

	cunit_test_t *test = (cunit_test_t *)calloc(1, sizeof(cunit_test_t));
	if (!test) { return; }

	test->name = name;
	test->func = test_func;

	cunit_test_suite_t *current_suite = g_cunit_registry.current_suite;
	if (!current_suite->tests) {
		current_suite->tests = test;
	} else {
		current_suite->last_test->next = test;
	}
	current_suite->last_test = test;
	current_suite->test_count++;
	g_cunit_registry.total_tests++;
}

// Runs all test suites.
int cunit_run(void) {
	g_cunit_registry.test_running = true;

	cunit_test_suite_t *suite = g_cunit_registry.suites;
	while (suite) {
		__cunit_print_suite_header(suite->name);
		cunit_test_t *test = suite->tests;
		while (test) {
			__cunit_run_test(suite, test);
			test = test->next;
		}
		__cunit_print_suite_summary(suite);
		suite = suite->next;
	}

	__cunit_print_final_summary();

	int failed_count = g_cunit_registry.total_failed;
	cunit_cleanup();
	return failed_count;
}

// Runs a specific test suite.
int cunit_run_suite(const char *suite_name) {
	cunit_test_suite_t *suite = g_cunit_registry.suites;
	while (suite) {
		if (strcmp(suite->name, suite_name) == 0) {
			g_cunit_registry.test_running = true;
			__cunit_print_suite_header(suite->name);
			cunit_test_t *test = suite->tests;
			while (test) {
				__cunit_run_test(suite, test);
				test = test->next;
			}
			__cunit_print_suite_summary(suite);
			g_cunit_registry.test_running = false;
			return suite->failed_count;
		}
		suite = suite->next;
	}
	return -1;  // Suite not found
}

// Sets the error handling mode.
void cunit_set_error_mode(cunit_error_mode_t mode) { g_cunit_registry.error_mode = mode; }

// Gets the total number of tests.
int cunit_get_number_of_tests(void) { return g_cunit_registry.total_tests; }

// Gets the total number of failed tests.
int cunit_get_number_of_failures(void) { return g_cunit_registry.total_failed; }

// Gets the total number of test suites.
int cunit_get_number_of_suites(void) {
	int                 count = 0;
	cunit_test_suite_t *suite = g_cunit_registry.suites;
	while (suite) {
		count++;
		suite = suite->next;
	}
	return count;
}
