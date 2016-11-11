/*
 * test-jsobj-constructor.h
 * Author: Keith Stellyes
 * Tests the different constructors for proper init. I doubt there'll ever be
 * any real issues here, but just in case.
 */
#pragma once
#include "../jsobj/js-obj.h"
#include "../jsobj/js-obj-functions.h"
#include "../test-functions/assertions.h"
#include "../misc.h"
#include "../uthash/utstring.h"
#include "../uthash/utlist.h"

#include<stdbool.h>
#include<stdio.h>
#include<time.h>

void __test_constructor_arr(assertparams) {
	JSObj::jsobj jo = new_jsobj_array();
	int result = get_jsobj_arraylen(jo);
	_asserteq_int("Initial array object init failed", 0, result);
	JSObj::jsobj hwjo = new_jsobj_str("Hello, World!");
	//DL_APPEND(jo.val.arrhead, &hwjo);
	jsobj_arrayappend(&jo, &hwjo);
	result = get_jsobj_arraylen(jo);
	_asserteq_int("Test first append len (string) failed", 1, result);
	_asserteq_str("Test first append tostring failed", "['Hello, World!']",
			jsobj_to_string(jo));
	JSObj::jsobj jod = new_jsobj_dbl(4);
	jsobj_arrayappend(&jo, &jod);
	result = get_jsobj_arraylen(jo);
	_asserteq_int("Test second append (double) failed", 2, result);
	_asserteq_str("Test second append (double) failed", "['Hello, World!',4.000000]",
			jsobj_to_string(jo));
	JSObj::jsobj j2 = new_jsobj_array();
	JSObj::jsobj hwwjo = new_jsobj_str("Hi, world");
	jsobj_arrayappend(&j2, &hwwjo);
	jsobj_arrayappend(&jo, &j2);
	result = get_jsobj_arraylen(jo);
	_asserteq_int("Test third append (array) failed", 3, result);
	_asserteq_str("Test third append tostring (array) failed",
			"['Hello, World!',4.000000,['Hi, world']]", jsobj_to_string(jo));

	time_t t = time(NULL);
	JSObj::jsobj jodt = new_jsobj_datetime(t);
	jsobj_arrayappend(&jo, &jodt);
	char* timestr = ctime(&t);
	*(timestr + (strlen(timestr)-1)) = '\0';
	char* expected_outputstr = (char*) calloc(1000, sizeof(char));
	strcat(expected_outputstr, "['Hello, World!',4.000000,['Hi, world'],'");
	strcat(expected_outputstr, timestr);
	strcat(expected_outputstr, "']");
	_asserteq_str("Test append (datetime) failed", expected_outputstr,
			jsobj_to_string(jo));
}

void __test_constructor_str(assertparams) {
	char* hw = "Hello, World!";
	JSObj::jsobj jo = new_jsobj_str(hw);
	_asserteq_str("Constructor with \"Hello, World!\" failed", hw,
			jsobj_to_string(jo));
	jo = new_jsobj_str("Hola, mundo");
	_asserteq_str("Constructor with \"Hola, mundo\" failed", "Hola, mundo",
			jsobj_to_string(jo));
	jo = new_jsobj_str("Hi, places");
	_asserteq_str("Constructor with \"Hi, places\" failed", "Hi, places",
			utstring_body(jo.val.s));
	set_joval_str(jo, hw);
	_asserteq_str("Setter with \"Hello, World!\" failed", hw,
			jsobj_to_string(jo));
}

void __test_constructor_dbl(assertparams) {
	JSObj::jsobj jo = new_jsobj_dbl(4.2);
	_asserteq_dbl("Constructor with \"4.2\" failed", 4.2, jo.val.d);
	char * s = (char*) malloc(50 * sizeof(char));
	snprintf(s, STRBUFF_DOUBLE, "%f", 4.2);
	//TODO: Move this toString() test elsewhere
	_asserteq_str("Constructor toString() failed :'(", s, jsobj_to_string(jo));
}

void __test_constructor_datetime(assertparams) {

	time_t currdt = time(NULL);
	JSObj::jsobj jo = new_jsobj_datetime(currdt);
	char* ctime_str = ctime(&currdt);
	char* jotime_strdirect = ctime(&currdt);
	strcat(jotime_strdirect, "'");

	char* jotime_tostring = jsobj_to_string(jo);

	_asserteq_str("Date time constructor failed", ctime_str, jotime_strdirect);
	_asserteq_str("Date time constructor failed", ctime_str, jotime_tostring);
}

void do_test_jsobj_constructor(assertparams) {
	__test_constructor_str(total, fails);
	__test_constructor_dbl(total, fails);
	__test_constructor_datetime(total, fails);
	__test_constructor_arr(total, fails);
}
