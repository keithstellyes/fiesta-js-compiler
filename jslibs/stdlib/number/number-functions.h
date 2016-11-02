/*
 * math-functions.h
 * Author: Keith Stellyes
 *
 */

#pragma once

#include "../../../js-obj.h"
#include "../../../js-obj-functions.h"
#include "../../../misc.h"
#include <stdlib.h>
#include <ctype.h>

jsobj jsf_Number_isFinite (jsobj jo) {
	return jo.type == jst_num;
}

