/*
 * test-console-log.h
 * Author: Keith Stellyes
 * Test console.log()
 */

#pragma once
#include "../../test-functions/assertions.h"

#include "../../misc.h"
#include "../../jsobj/js-obj.h"
#include "../../jsobj/js-obj-functions.h"
#include "../../jslibs/stdlib/console/jsf_console.h"
#include "../largetext.h"
#include "../globals-testenv.h"

#include<stdbool.h>
#include<stdio.h>

void __tst1arg(int* total, int* fails) {
	JSObj::jsobj jo = new_jsobj_str("Hello, World!");
	_flushjsstdout();
	jsf_console__log(1, &jo);
	_asserteq_strjsstdout("console.log(\"Hello, World!\" failed.", "Hello, World! \n");
}

void __tstmanyargs(int* total, int* fails) {
	JSObj::jsobj args[2];
	JSObj::jsobj j1 = new_jsobj_str("Hello,");
	JSObj::jsobj j2 = new_jsobj_str("World!");
	args[0] = j1;
	args[1] = j2;
	_flushjsstdout();
	jsf_console__log(2, args);
	_asserteq_strjsstdout("console.log(\"Hello,\", \"World!\") failed", "Hello, World! \n");

	JSObj::jsobj args2[3];
	j1 = new_jsobj_str("Hello,");
	j2 = new_jsobj_str("World!");
	JSObj::jsobj j3 = new_jsobj_dbl(4.2);
	args2[0] = j1;
	args2[1] = j2;
	args2[2] = j3;
	_flushjsstdout();
	jsf_console__log(3, args2);

	_asserteq_strjsstdout("console.log(\"Hello,\", \"World!\", 4.2) failed", "Hello, World! 4.200000 \n");

	args2[0] = j1;
	args2[1] = j2;
	args2[2] = j3;
	_flushjsstdout();
	jsf_console__log(3, args2);
}

void do_console_log_test(int* total, int* fails) {
	__tst1arg(total, fails);
	__tstmanyargs(total, fails);
}
