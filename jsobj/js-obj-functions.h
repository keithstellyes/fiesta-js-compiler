/*
 * js-obj-functions.h
 * Author: Keith Stellyes
 *
 * Note that these are mainly _internal_ functions, many of which are used to
 * implement JS functions. All JS functions return an object, but many of these
 * functions do not. However, many JS functions implemented in this compiler
 * will likely use these for implementation. For example, this implements a
 * toString() function that returns a raw string, as opposed to a JS object.
 * Many JS functions use a toString() internally anyway, this will help with
 * speed and simplicity of development.
 */

#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "js-obj.h"
#include "../uthash/utstring.h"
#include "../uthash/utlist.h"

#define STRBUFF_DOUBLE 30
#define STRBUFF_ARROUTPUT 2000
/* getters; setters */
#define get_jotype(joarg) joarg.type
#define set_jotype(joarg, jotypearg) joarg.type = jotype
#define set_joval_str(joarg, sarg) utstring_new(joarg.val.s); utstring_printf(joarg.val.s, sarg)
#define get_joval_string(joarg) utstring_body(joarg.val.s)
#define get_joval_datetime(joarg) joarg.val.tim
#define get_joval_dbl(joarg) joarg.val.d

void jsobj_arrayappend(jsobj* joarg, jsobj* newelement) {
	DL_APPEND(joarg->val.arrhead, newelement);
}


char* jsobj_to_string(jsobj jo) {
    if (jo.type == jst_num) {
        char* string_output = malloc(STRBUFF_DOUBLE);
        snprintf(string_output, STRBUFF_DOUBLE-1, "%f", jo.val.d);
        return string_output;
    } else if (jo.type == jst_bool) {
        if (jo.val.b == true) {
            return "true";
        }
        return "false";
    } else if (jo.type == jst_str) {
    	return get_joval_string(jo);
    } else if (jo.type == jst_datetime) {
    	char* _s = calloc(STRBUFF_ARROUTPUT, sizeof(char));
    	char* ctime_str = ctime(&jo.val.tim);
    	*(ctime_str + (strlen(ctime_str)-1)) = '\0';
    	strcat(_s, ctime_str);
    	return _s;
    } else if (jo.type == jst_arr) {
    	jsobj* elt;
    	jsobj* tmp;

    	char* string_output = calloc(STRBUFF_ARROUTPUT, sizeof(char));

    	DL_FOREACH_SAFE(jo.val.arrhead, elt, tmp) {
    		//jsobj_type jot = get_jotype(*elt->val.arrhead);
    		jsobj_type jot = elt->type;

    		if (jot != jst_num && jot != jst_arr) {
    			//i += sprintf(string_output, "'%s',",jsobj_to_string(*elt));
    			strcat(string_output, "'");
    			strcat(string_output, jsobj_to_string(*elt));
    			strcat(string_output, "'");
    		} else {
    			//i += sprintf(string_output, "%s,",jsobj_to_string(*elt->elptr));
    			//i += sprintf(string_output, "%s,",jsobj_to_string(*elt));
    			strcat(string_output, jsobj_to_string(*elt));
    		}
    		strcat(string_output, ",");
    	}
    	char* final_string_output = calloc(STRBUFF_ARROUTPUT, sizeof(char));

    	//char* delet = strstr(string_output, ",\0");
    	*(string_output + (strlen(string_output)-1)) = '\0';

    	sprintf(final_string_output, "[%s]", string_output);
    	return final_string_output;
    }
    else {
    	return "Undefined";
    }
}

int get_jsobj_arraylen(jsobj jo) {
	int count = 0;
	//Required for the function, but thrown away value.
	jsobj* elt_placeholder;
	DL_COUNT(jo.val.arrhead, elt_placeholder, count);
	return count;
}

/*void jsobj_arrayappend(jsobj jo, jsobj newelement) {
	jsarr_el eltoadd;
	eltoadd.elptr = &newelement;
	DL_APPEND(jo.val.arrhead, &eltoadd);
}*/

jsobj new_jsobj_array() {
	jsobj jo;
	jo.type = jst_arr;
	jo.val.arrhead = NULL;
	return jo;
}

jsobj new_jsobj_datetime(time_t t) {
	jsobj jo;
	jo.type = jst_datetime;
	jo.val.tim = t;
	return jo;
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
