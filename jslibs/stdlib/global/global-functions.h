/*
 * global-functions.h
 * Author: Keith Stellyes
 *
 */

#pragma once

#include "../../../jsobj/js-obj.h"
#include "../../../jsobj/js-obj-functions.h"

jsobj jsf_isNaN(jsobj jo) {
	return get_jotype(jo) == jst_nan;
}

jsobj jsf_parseFloat(jsobj jo) {
	if (get_jotype(jo) == jst_pinf || get_jotype(jo) == jst_ninf) {
		return new_jsobj_bytype(jo.type);
	}
	return jsobj_str_to_dbl(jo);
}
