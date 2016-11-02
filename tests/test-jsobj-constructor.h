/*
 * test-jsobj-constructor.h
 * Author: Keith Stellyes
 * Tests the different constructors for proper init. I doubt there'll ever be
 * any real issues here, but just in case.
 */
#pragma once
#include "../js-obj.h"
#include "../js-obj-functions.h"
#include "../js-string.h"
#include "../test-functions/assertions.h"
#include "../misc.h"
#include "../uthash/utstring.h"

#include<stdbool.h>
#include<stdio.h>

void test_constructor_str(assertparams) {
	jsobj jo = new_jsobj_str("Hello, World!");
	_asserteq_str("Constructor with \"Hello, World!\" failed", "Hello, World!",
			jsobj_to_string(jo));
	jo = new_jsobj_str("Hola, mundo");
	_asserteq_str("Constructor with \"Hola, mundo\" failed", "Hola, mundo",
			jsobj_to_string(jo));
	jo = new_jsobj_str("Hi, places");
	_asserteq_str("Constructor with \"Hi, places\" failed", "Hi, places",
			utstring_body(jo.val.s));
}

void test_constructor_dbl(assertparams) {
	jsobj jo = new_jsobj_dbl(4.2);
	_asserteq_dbl("Constructor with \"4.2\" failed", 4.2, jo.val.d);
	char * s = malloc(50 * sizeof(char));
	snprintf(s, STRBUFF_DOUBLE, "%f", 4.2);
	//TODO: Move this toString() test elsewhere
	_asserteq_str("Constructor toString() failed :'(", s, jsobj_to_string(jo));
}

void do_test_jsobj_constructor(assertparams) {
	test_constructor_str(total, fails);
	test_constructor_dbl(total, fails);
}
