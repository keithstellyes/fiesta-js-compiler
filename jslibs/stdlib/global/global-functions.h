/*
 * global-functions.h
 * Author: Keith Stellyes
 *
 */

#pragma once

#include "../../../js-obj.h"
#include "../../../js-obj-functions.h"

jsobj jsf_isNaN(jsobj jo) {
	return jo.type == jst_nan;
}

jsobj jsf_parseFloat(jsobj jo) {
	if (jo.type == jst_pinf || jo.type == jst_ninf) {
		return new_jsobj_bytype(jo.type);
	}
	return jsobj_str_to_dbl(jo);
}
