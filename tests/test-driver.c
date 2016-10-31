/*
 * test-driver.c
 * Author: Keith Stellyes
 * Calls all the different main test functions.
 */
#include "test-jsobj-constructor.h"
#include "../test-functions/assertions.h"
#include "test-jsstring.h"
#include "stdlib/test-console-log.h"
#include "stdlib/test-math.h"
#include <stdlib.h>

int main() {
	int total = 0;
	int fails = 0;
	do_test_jsobj_constructor(&total, &fails);
	do_test_jsstring(&total, &fails);
	do_console_log_test(&total, &fails);
	do_stdlibtest_math(&total, &fails);
	print_test_results();
	printf("%d\n", RAND_MAX);
	return 0;
}
