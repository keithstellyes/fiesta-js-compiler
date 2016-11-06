/*
 * math-functions.h
 * Author: Keith Stellyes
 *
 */

#pragma once

#include "../../../jsobj/js-obj.h"
#include "../../../jsobj/js-obj-functions.h"
#include "../../../misc.h"
#include <stdlib.h>
#include <ctype.h>

jsobj jsf_Number_isFinite (jsobj jo) {
	return get_jotype(jo) == jst_num;
}

