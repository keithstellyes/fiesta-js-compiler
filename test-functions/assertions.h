/*
 * assertions.h
 * Author: Keith Stellyes
 * A basic assertions header for use by the test drivers, and various other
 * macros to make writing new tests as simple as possible.
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../misc.h"
#include "../jsobj/js-obj.h"
#include "../tests/globals-testenv.h"

#define out printf
#define assertparams int* total, int* fails

#define asserter(condition, fmtstr) *total += 1;\
	if(condition) return true;\
	else { out(fmtstr, msg, expected, actual); *fails += 1; return false; }

#define asserteq(fmtstr) asserter(expected == actual, fmtstr)

#define _asserteq_str(msg, expected, actual) asserteq_str(total, fails, msg, expected, actual)
#define _asserteq_strjsstdout(msg, expected) asserteq_str(total, fails, msg, expected, _JSSTDOUT)

#define _asserteq_dbl(msg, expected, actual) asserteq_dbl(total, fails, msg, expected, actual)
#define _asserteq_jstype(msg, expected, actual) asserteq_jstype(total, fails, msg, expected, actual)
#define _asserteq_int(msg, expected, actual) asserteq_int(total, fails, msg, expected, actual)
#define _asserteq_typ(msg, expected, actual) asserteq_typ(total, fails, msg, expected, actual)

#define print_test_results() printf("\n%d/%d tests passed.\n", total-fails, total)

bool asserteq_str(int* total, int* fails, char* msg, char* expected, char* actual) {
	asserter(strcmp(expected,actual) == 0,
			"%s.\nExpected:\"%s\", Actual:\"%s\"\n");
}

bool asserteq_dbl(int* total, int* fails, char* msg, double expected, double actual) {
	asserteq("%s.\nExpected:\"%f\", Actual:\"%f\"\n");
}

bool asserteq_int(int* total, int* fails, char* msg, int expected, int actual) {
	asserteq("%s.\nExpected:\"%d\", Actual:\"%d\"\n");
}

bool asserteq_typ(int* total, int* fails, char* msg, JSObj::jsobj_type expected, JSObj::jsobj_type actual) {
	asserteq("Incorrect type.");
}
