/*
 * test-console-log.h
 * Author: Keith Stellyes
 * Test console.log()
 */

#pragma once
#include "../../test-functions/assertions.h"

#include "../../misc.h"
#include "../../js-obj.h"
#include "../../js-obj-functions.h"
#include "../../js-string.h"
#include "../../jslibs/stdlib/console/jsf_console.h"
#include "../largetext.h"

#include<stdbool.h>
#include<stdio.h>

void tst1arg(int* total, int* fails) {
	jsobj jo = new_jsobj_str("Hello, World!");
	jsf_console__log(1, &jo);
}

void tstmanyargs(int* total, int* fails) {
	jsobj args[2];
	jsobj j1 = new_jsobj_str("Hello,");
	jsobj j2 = new_jsobj_str("World!");
	args[0] = j1;
	args[1] = j2;
	jsf_console__log(2, args);

	jsobj args2[3];
	j1 = new_jsobj_str("Hello,");
	j2 = new_jsobj_str("World!");
	jsobj j3 = new_jsobj_dbl(4.2);

	args2[0] = j1;
	args2[1] = j2;
	args2[2] = j3;
	jsf_console__log(3, args2);
}

void do_console_log_test(int* total, int* fails) {
	printf("===begin console.log() test===\n");
	tst1arg(total, fails);
	tstmanyargs(total, fails);
	printf("===end console.log() test===\n");
}
