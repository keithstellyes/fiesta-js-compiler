/*
 * jsf_console.h
 * Author: Keith Stellyes
 * The console object used by many implementations.
 */
#pragma once

#include "../../../js-obj.h"
#include "../../../js-obj-functions.h"


#ifdef __BUILDOP_TST
#include "../../../tests/globals-testenv.h"
#define _printf(...) char* _snprintftmpbfr = (char*) malloc(_JSSTDOUT_BUFFSIZE);\
snprintf(_snprintftmpbfr, _JSSTDOUT_BUFFSIZE, __VA_ARGS__);\
char* _snprintftmpbfr2 = (char*) malloc(_JSSTDOUT_BUFFSIZE);\
snprintf(_snprintftmpbfr2, _JSSTDOUT_BUFFSIZE, "%s%s", _JSSTDOUT, _snprintftmpbfr);\
strcpy(_JSSTDOUT, _snprintftmpbfr2);
#endif

jsobj jsf_console__log(int argc, jsobj* args) {
	while(argc--) {
		char* s = jsobj_to_string(*args);
		_printf("%s ", s);
		args++;
	}
	_printf("\n");
	return new_jsobj_undef();
}
