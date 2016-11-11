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

#define is_jsobj_numberobj(joarg) (get_jotype(joarg) == JSObj::jst_num || get_jotype(joarg) == JSObj::jst_pinf \
    || get_jotype(joarg) == JSObj::jst_ninf || get_jotype(joarg) == JSObj::jst_nan)

#define is_jsobj_strorarrlen1(joarg) (get_jotype(joarg) == JSObj::jst_arr && get_jsobj_arraylen(joarg) == 1)

void jsobj_arrayappend(JSObj::jsobj* joarg, JSObj::jsobj* newelement) {
	DL_APPEND(joarg->val.arrhead, newelement);
}


char* jsobj_to_string(JSObj::jsobj jo) {
    if (jo.type == JSObj::jst_num) {
        char* string_output = (char*) malloc(STRBUFF_DOUBLE);
        snprintf(string_output, STRBUFF_DOUBLE-1, "%f", jo.val.d);
        return string_output;
    } else if (jo.type == JSObj::jst_bool) {
        if (jo.val.b == true) {
            return "true";
        }
        return "false";
    } else if (jo.type == JSObj::jst_str) {
    	return get_joval_string(jo);
    } else if (jo.type == JSObj::jst_datetime) {
    	char* _s = (char*) calloc(STRBUFF_ARROUTPUT, sizeof(char));
    	char* ctime_str = ctime(&jo.val.tim);
    	*(ctime_str + (strlen(ctime_str)-1)) = '\0';
    	strcat(_s, ctime_str);
    	return _s;
    } else if (jo.type == JSObj::jst_arr) {
    	JSObj::jsobj* elt;
    	JSObj::jsobj* tmp;

    	char* string_output = (char*) calloc(STRBUFF_ARROUTPUT, sizeof(char));

    	DL_FOREACH_SAFE(jo.val.arrhead, elt, tmp) {
    		//jsobj_type jot = get_jotype(*elt->val.arrhead);
    		JSObj::jsobj_type jot = elt->type;

    		if (jot != JSObj::jst_num && jot != JSObj::jst_arr) {
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
    	char* final_string_output = (char*) calloc(STRBUFF_ARROUTPUT, sizeof(char));

    	//char* delet = strstr(string_output, ",\0");
    	*(string_output + (strlen(string_output)-1)) = '\0';

    	sprintf(final_string_output, "[%s]", string_output);
    	return final_string_output;
    }
    else {
    	return "Undefined";
    }
}

int get_jsobj_arraylen(JSObj::jsobj jo) {
	int count = 0;
	//Required for the function, but thrown away value.
	JSObj::jsobj* elt_placeholder;
	DL_COUNT(jo.val.arrhead, elt_placeholder, count);
	return count;
}

/*void jsobj_arrayappend(jsobj jo, jsobj newelement) {
	jsarr_el eltoadd;
	eltoadd.elptr = &newelement;
	DL_APPEND(jo.val.arrhead, &eltoadd);
}*/

JSObj::jsobj new_jsobj_array() {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_arr;
	jo.val.arrhead = NULL;
	return jo;
}

JSObj::jsobj new_jsobj_datetime(time_t t) {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_datetime;
	jo.val.tim = t;
	return jo;
}

JSObj::jsobj new_jsobj_str(char* s) {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_str;
	UT_string* uts;
	utstring_new(uts);
	utstring_printf(uts, s);
	jo.val.s = uts;
	return jo;
}

JSObj::jsobj new_jsobj_dbl(double d) {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_num;
	jo.val.d = d;
	return jo;
}

JSObj::jsobj new_jsobj_nan() {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_nan;
	return jo;
}

JSObj::jsobj new_jsobj_bytype(JSObj::jsobj_type jt) {
	JSObj::jsobj jo;
	jo.type = jt;
	return jo;
}

JSObj::jsobj new_jsobj_bool(bool b) {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_bool;
	jo.val.b = b;
	return jo;
}

JSObj::jsobj new_jsobj_undef() {
	JSObj::jsobj jo;
	jo.type = JSObj::jst_nan;
	return jo;
}

bool str_canbe_dbl(char* s) {
	char c = *(s);
	bool has_digit = false;
	int neg_ctr = 0;
	int dot_ctr = 0;
	int i = 0;
	while(c != '\0') {
		if(isdigit(c)) {
			has_digit = true;
		} else if(c == '-') {
			neg_ctr++;
		} else if(c == '.') {
			dot_ctr++;
		}
		else if(!isspace(c)) {
			return false;
		}

		c = *(s + ++i);
	}
	if(has_digit && neg_ctr <= 1 && dot_ctr <= 1) {
		return true;
	}
	return false;
}

/* If it's a 1 el array or just a string, it'll attempt to parse it, if it's a
 * double, it'll just return itself. Otherwise, returns NaN.
 */
JSObj::jsobj jsobj_todbl(JSObj::jsobj jo) {
	char* jo_str;
	if (get_jotype(jo) == JSObj::jst_str) {
		jo_str = utstring_body(jo.val.s);
	} else if (is_jsobj_strorarrlen1(jo)) {
		JSObj::jsobj* elttemp;
		DL_FOREACH(jo.val.arrhead, elttemp) {
			JSObj::jsobj jotemp = *elttemp;
			jo_str = get_joval_string(jotemp);
		}
	} else if (get_jotype(jo) == JSObj::jst_num){
		return jo;
	} else {
		return new_jsobj_nan();
	}
	char* s = get_joval_string(jo);
	if (str_canbe_dbl(s)) {
		return new_jsobj_dbl(strtod(jo_str, NULL));
	}
	return new_jsobj_nan();
}

// ==
// see:
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Equality_comparisons_and_sameness
bool loose_equality(JSObj::jsobj j1, JSObj::jsobj j2) {
	if (j1.type == j2.type) {
		if(j1.type == JSObj::jst_nan
			|| j1.type == JSObj::jst_pinf
			|| j1.type == JSObj::jst_ninf
			|| j1.type == JSObj::jst_undef
			|| j1.type == JSObj::jst_null) {
			return true;
		}
	}
	return false;
}
JSObj::jsobj jsobj_loose_equality(JSObj::jsobj j1, JSObj::jsobj j2) {
	return new_jsobj_bool(loose_equality(j1, j2));
}

// ===
// see:
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Equality_comparisons_and_sameness
bool strict_equality(JSObj::jsobj j1, JSObj::jsobj j2) {
	if (j1.type != j2.type
	     || j1.type == JSObj::jst_nan
	     || j2.type == JSObj::jst_nan) {
		return false;
	}
	return loose_equality(j1, j2);
}
JSObj::jsobj jsobj_strict_equality(JSObj::jsobj j1, JSObj::jsobj j2) {
	return new_jsobj_bool(strict_equality(j1, j2));
}
