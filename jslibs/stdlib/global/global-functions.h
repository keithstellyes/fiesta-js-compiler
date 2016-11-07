/*
 * global-functions.h
 * Author: Keith Stellyes
 *
 */

#pragma once

#include "../../../jsobj/js-obj.h"
#include "../../../jsobj/js-obj-functions.h"
#include<stdbool.h>
#include<math.h>

#define out printf

jsobj jsf_isNaN(jsobj jo) {
	return new_jsobj_bool(get_jotype(jo) == jst_nan);
}

jsobj jsf_parseFloat(jsobj jo) {
	if (get_jotype(jo) == jst_pinf || get_jotype(jo) == jst_ninf) {
		return new_jsobj_bytype(jo.type);
	}
	return jsobj_todbl(jo);
}

jsobj jsf_parseInt(jsobj jo) {
	if(get_jotype(jo) == jst_num || is_jsobj_strorarrlen1(jo)) {
		jsobj jotmp = jsf_parseFloat(jo);
		if (get_jotype(jo) == jst_num) {
			return new_jsobj_dbl(floor(jo.val.d));
		}
	}
	return new_jsobj_nan();
}

jsobj jsf_isFinite(jsobj jo) {
	if (get_jotype(jo) == jst_num) {
		return new_jsobj_bool(true);
	}
	else if (is_jsobj_strorarrlen1(jo)) {
		bool b = get_jotype(jsobj_todbl(jo)) == jst_num;
		return new_jsobj_bool(b);
	} else {
		return new_jsobj_bool(false);
	}
}

jsobj jsf_alert(jsobj jo) {
#ifdef __BUILDOP_SHELLAPP
	char* red_colorcode = "\033[31m";
	char* end_colorcode = "\033[m";
	char* s = jsobj_to_string(jo);
	out("%s%s%s\n", red_colorcode, s, end_colorcode);
#endif
	return new_jsobj_bytype(jst_undef);
}

jsobj jsf_prompt(jsobj jo) {
#ifdef __BUILDOP_SHELLAPP
	printf(get_joval_string(jo));
	char promptstring [10000];
	scanf("%s", promptstring);
	return new_jsobj_str(promptstring);
#endif
	return new_jsobj_bytype(jst_undef);
}

jsobj jsf_typeof(jsobj jo) {
	if(is_jsobj_numberobj(jo)) {
		return new_jsobj_string("number");
	} else if (get_jotype(jo) == jst_str) {
		return new_jsobj_string("string");
	} else if (get_jotype(jo) == jst_arr || get_jotype(jo) == jst_datetime) {
		return new_jsobj_string("object");
	} else if (get_jotype(jo) == jst_null) {
		return new_jsobj_string("null");
	} else {
		return new_jsobj_string("undefined");
	}
}



