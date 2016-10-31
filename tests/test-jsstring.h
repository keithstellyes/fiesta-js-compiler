/*
 * test-jsstring.h
 * Author: Keith Stellyes
 * Tests the internal string data type used in strings.
 */

#pragma once
#include "../test-functions/assertions.h"

#include "../misc.h"
#include "../js-obj.h"
#include "../js-obj-functions.h"
#include "../js-string.h"
#include "largetext.h"

#include<stdbool.h>
#include<stdio.h>

#define hw "Hello, World!"
#define hw_js() new_jsstring(hw)
#define hw_len strlen(hw)

void test_init(assertparams) {
	jsstring jss = hw_js();
	char* s = "Hello, World!";
	_asserteq_str("String data type init failed with value \"Hello, World!\" failed",
			s, jss.s);
	_asserteq_int("String data type init failed with correct chunksize for size <STRCHNUK",
			STRCHUNK, jss.arrlen);
	_asserteq_int("String data type init failed. Incorrect char counter.", strlen(s),
			jss.total_chars);
	_asserteq_int("String space left is incorrect.", STRCHUNK - strlen(s),
			space_left_in_jsstring(jss));

	jss = new_jsstring(s1000);
	_asserteq_str("String data type init failed with string of STRCHUNK size failed",
			s1000, jss.s);
	_asserteq_int("String data type init failed with correct chunksize for size <STRCHNUK",
			STRCHUNK, jss.arrlen);
	_asserteq_int("String data type init failed. Incorrect char counter.", strlen(s1000),
			jss.total_chars);
	_asserteq_int("String space left is incorrect.", 0, space_left_in_jsstring(jss));

	jss = new_jsstring(s1005);
	_asserteq_str("String data type init failed with string of STRCHUNK size failed",
			s1005, jss.s);
	_asserteq_int("String data type init failed with correct chunksize for size <STRCHNUK",
			STRCHUNK*2, jss.arrlen);
	_asserteq_int("String data type init failed. Incorrect char counter.", strlen(s1005),
			jss.total_chars);
	_asserteq_int("String space left is incorrect.", 995,
			space_left_in_jsstring(jss));
}

void test_append(assertparams) {
	jsstring jss = hw_js();
	append_to_jsstring(&jss, "!");
	_asserteq_str("Append failed, should be Hello, World!!", "Hello, World!!",
			jss.s);
	_asserteq_int("Append failure. Inaccurate charlen", hw_len + 1, jss.total_chars);
	_asserteq_int("Append failure. Inaccurate internal arrlen", STRCHUNK, jss.arrlen);
	_asserteq_int("Append failure. Inaccurate space left.", 986, space_left_in_jsstring(jss));

	append_to_jsstring(&jss, s1000);
	_asserteq_str("Append failure during op requiring chunks needing to be grabbed.",
			HWS1014, jss.s);
	_asserteq_int("Append failure during op requiring chunks needing to be grabbed.\
\nBad charlen", 1014, jss.total_chars);
	_asserteq_int("Append failure during op requiring chunks needing to be grabbed.\
\nBad arrlen", STRCHUNK*2, jss.arrlen);
	_asserteq_int("Append failure during op requiring chunks needing to be grabbed.\
\nInaccurate space left.", 986, space_left_in_jsstring(jss));

	//testing getting 2 more chunks at a time
	jss = hw_js();
	append_to_jsstring(&jss, s2000);
	_asserteq_str("Append failed during op requiring multiple chunks needing to be\
grabbed.\n", s2013, jss.s);
	_asserteq_int("0...", strlen(s2013), jss.total_chars);
	_asserteq_int("1...", 987, space_left_in_jsstring(jss));
}

void do_test_jsstring(int* total, int* fails) {
	test_init(total, fails);
	test_append(total, fails);
}
