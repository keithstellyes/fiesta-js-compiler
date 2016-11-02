/*
 * js-obj-functions.h
 * Author: Keith Stellyes
 *
 * Note that these are _internal_ functions, and not necessarily callable by
 * standard JavaScript. Most of the stdlib implementations will likely be
 * using these at least to write them, such as the to_string functions.
 * Some stdlib implementations of functions may literally only be a call
 * to one of these.
 */

#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "js-obj.h"
#include "js-string.h"
#include "uthash/utstring.h"

#define STRBUFF_DOUBLE 30

char* jsobj_to_string(jsobj jo) {
    if (jo.type == jst_num) {
        char* string_output = malloc(STRBUFF_DOUBLE);
        snprintf(string_output, STRBUFF_DOUBLE-1, "%f", jo.val.d);
        return string_output;
    }
    else if (jo.type == jst_bool) {
        if (jo.val.b == true) {
            return "true";
        }
        return "false";
    }

    else if (jo.type == jst_str) {
    	return utstring_body(jo.val.s);
    }

    else {
    	return "Undefined";
    }
}

jsobj new_jsobj_str(char* s) {
	jsobj jo;
	jo.type = jst_str;
	UT_string* uts;
	utstring_new(uts);
	utstring_printf(uts, s);
	jo.val.s = uts;
	return jo;
}

jsobj new_jsobj_dbl(double d) {
	jsobj jo;
	jo.type = jst_num;
	jo.val.d = d;
	return jo;
}

jsobj new_jsobj_nan() {
	jsobj jo;
	jo.type = jst_nan;
	return jo;
}

jsobj new_jsobj_bytype(jsobj_type jt) {
	jsobj jo;
	jo.type = jt;
	return jo;
}

jsobj new_jsobj_bool(bool b) {
	jsobj jo;
	jo.type = jst_bool;
	jo.val.b = b;
	return jo;
}

jsobj new_jsobj_undef() {
	jsobj jo;
	jo.type = jst_nan;
	return jo;
}

jsobj jsobj_str_to_dbl(jsobj jo) {
	int i = 0;
	char* jo_str = utstring_body(jo.val.s);
	char c = *(jo_str);
	bool has_digit = false;
	int neg_ctr = 0;
	int dot_ctr = 0;

	while(c != '\0') {
		if(isdigit(c)) {
			has_digit = true;
		} else if(c == '-') {
			neg_ctr++;
		} else if(c == '.') {
			dot_ctr++;
		}
		else if(!isspace(c)) {
			return new_jsobj_bytype(jst_nan);
		}

		c = *(jo_str + ++i);
	}
	if(has_digit && neg_ctr <= 1 && dot_ctr <= 1) {
		return new_jsobj_dbl(strtod(jo_str, NULL));
	}
	return new_jsobj_nan();
}

// ==
// see:
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Equality_comparisons_and_sameness
bool loose_equality(jsobj j1, jsobj j2) {
	if (j1.type == j2.type) {
		if(j1.type == jst_nan
			|| j1.type == jst_pinf
			|| j1.type == jst_ninf
			|| j1.type == jst_undef
			|| j1.type == jst_null) {
			return true;
		}
	}
	return false;
}
jsobj jsobj_loose_equality(jsobj j1, jsobj j2) {
	return new_jsobj_bool(loose_equality(j1, j2));
}

// ===
// see:
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Equality_comparisons_and_sameness
bool strict_equality(jsobj j1, jsobj j2) {
	if (j1.type != j2.type
	     || j1.type == jst_nan
	     || j2.type == jst_nan) {
		return false;
	}
	return loose_equality(j1, j2);
}
jsobj jsobj_strict_equality(jsobj j1, jsobj j2) {
	return new_jsobj_bool(strict_equality(j1, j2));
}
