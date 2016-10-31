/*
 * functions.h
 * Author: Keith Stellyes
 * The methods of the Math built-in
 */

#pragma once

#include "../../../js-obj.h"
#include "../../../js-obj-functions.h"
#include "../../../misc.h"
#include <stdlib.h>
#include <ctype.h>

/*
 * if number, return -1 if <0, 0 if 0, 1 if >0 (incl. infinity)
 * It will try to convert it to a num if it's a str
 * Otherwise, return NaN
 */

jsobj jsf_Math_sign(jsobj jo) {
	if(jo.type == jst_num) {
		if(jo.val.d < 0) {
			return new_jsobj_dbl(-1);\
		}
		else if(jo.val.d == 0) {
			return new_jsobj_dbl(0);
		}
		else if(jo.val.d > 0) {
			return new_jsobj_dbl(1);
		}
		else {
			return new_jsobj_dbl(0);
		}
	}
	else if(jo.type == jst_ninf) {
		return new_jsobj_dbl(-1);
	}
	else if(jo.type == jst_pinf) {
		return new_jsobj_dbl(1);
	}
	else if(jo.type == jst_null) {
		return new_jsobj_dbl(0);
	}
	else if(jo.type == jst_str) {
		return jsf_Math_sign(jsobj_str_to_dbl(jo));
	}
	return new_jsobj_bytype(jst_nan);
}

jsobj jsf_Math_random() {
	return new_jsobj_dbl(rand_md());
}
