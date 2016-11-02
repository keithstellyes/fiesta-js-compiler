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
#include <math.h>

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

jsobj jsf_Math_sinh(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(sinh(jo.val.d));
}
jsobj jsf_Math_pow(jsobj j1, jsobj j2) {
    if (j1.type != jst_num || j2.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(pow(j1.val.d, j2.val.d));
}
jsobj jsf_Math_asinh(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(asinh(jo.val.d));
}
jsobj jsf_Math_ceil(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(ceil(jo.val.d));
}
jsobj jsf_Math_atan2(jsobj j1, jsobj j2) {
    if (j1.type != jst_num || j2.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atan2(j1.val.d, j2.val.d));
}
jsobj jsf_Math_asin(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(asin(jo.val.d));
}
jsobj jsf_Math_atanh(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atanh(jo.val.d));
}
jsobj jsf_Math_exp(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(exp(jo.val.d));
}
jsobj jsf_Math_tan(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(tan(jo.val.d));
}
jsobj jsf_Math_log(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(log(jo.val.d));
}
jsobj jsf_Math_log10(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(log10(jo.val.d));
}
jsobj jsf_Math_acos(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(acos(jo.val.d));
}
jsobj jsf_Math_atan(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atan(jo.val.d));
}
jsobj jsf_Math_tanh(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(tanh(jo.val.d));
}
jsobj jsf_Math_sin(jsobj jo) {
    if (jo.type != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(sin(jo.val.d));
}

