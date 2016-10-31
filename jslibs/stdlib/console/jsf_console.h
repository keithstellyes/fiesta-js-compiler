/*
 * jsf_console.h
 * Author: Keith Stellyes
 * The console object used by many implementations.
 */
#pragma once

#include "../../../js-obj.h"
#include "../../../js-obj-functions.h"

void jsf_console__log(int argc, jsobj* args) {
	while(argc--) {
		char* s = jsobj_to_string(*args);
		printf("%s ", s);
		args++;
	}
	printf("\n");
}
