/*
 * test-driver.c
 * Author: Keith Stellyes
 * Calls all the different main test functions.
 */
#ifdef __BUILDOP_TST
#include "test-jsobj-constructor.h"
#include "../test-functions/assertions.h"
#include "stdlib/test-console-log.h"
#include "stdlib/test-math.h"
#include <stdlib.h>
#include "../jsobj/js-func.h"
#include "../misc.h"
#include "../uthash/utstring.h"
#include "globals-testenv.h"
#include "test-assertions.h"

int main() {
	int total = 0;
	int fails = 0;
	_init_globals_testenv();
	do_test_assertions(&total, &fails);
	do_test_jsobj_constructor(&total, &fails);
	do_console_log_test(&total, &fails);
	do_stdlibtest_math(&total, &fails);
	print_test_results();
	printf("%d\n", sizeof(jsobj));

	return 0;
}
#endif
