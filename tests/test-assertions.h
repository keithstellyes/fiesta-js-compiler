/*
 * test-assertions.h
 * Author: Keith Stellyes
 *
 * Test my assertion header that I wrote
 */

#pragma once
#include "../test-functions/assertions.h"
#include "../jsobj/js-obj.h"
#include "globals-testenv.h"
#include "../jslibs/stdlib/console/jsf_console.h"
#include <stdbool.h>

void __test_asserteq_str(assertparams) {
 	_asserteq_str("_assereq_str bad", "a", "a");
 	jsobj jo = new_jsobj_str("hw");
 	jsf_console__log(1, &jo);
 	_asserteq_dbl("_asserteq_dbl bad", 4.2, 4.2);
 	_asserteq_int("_asserteq_int bad", 3, 3);
 	_asserteq_typ("_asserteq_jstype bad", jst_str, jst_str);
}

void do_test_assertions(assertparams) {
	__test_asserteq_str(total, fails);
}

