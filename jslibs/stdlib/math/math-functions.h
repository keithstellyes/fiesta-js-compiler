/*
 * functions.h
 * Author: Keith Stellyes
 * The methods of the Math built-in
 */

#pragma once

#include "../../../jsobj/js-obj.h"
#include "../../../jsobj/js-obj-functions.h"
#include "../../../misc.h"
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/*
 * if number, return -1 if <0, 0 if 0, 1 if >0 (incl. infinity)
 * It will try to convert it to a num if it's a str
 * Otherwise, return NaN
 */

JSObj::jsobj jsf_Math_sign(JSObj::jsobj jo) {
	if(get_jotype(jo) == JSObj::jst_num) {
		if(get_joval_dbl(jo) < 0) {
			return new_jsobj_dbl(-1);\
		}
		else if(get_joval_dbl(jo) == 0) {
			return new_jsobj_dbl(0);
		}
		else if(get_joval_dbl(jo) > 0) {
			return new_jsobj_dbl(1);
		}
		else {
			return new_jsobj_dbl(0);
		}
	}
	else if(get_jotype(jo) == JSObj::jst_ninf) {
		return new_jsobj_dbl(-1);
	}
	else if(get_jotype(jo) == JSObj::jst_pinf) {
		return new_jsobj_dbl(1);
	}
	else if(get_jotype(jo) == JSObj::jst_null) {
		return new_jsobj_dbl(0);
	}
	else if(get_jotype(jo) == JSObj::jst_str) {
		return jsf_Math_sign(jsobj_todbl(jo));
	}
	return new_jsobj_bytype(JSObj::jst_nan);
}

JSObj::jsobj jsf_Math_random() {
	return new_jsobj_dbl(rand_md());
}

JSObj::jsobj jsf_Math_sinh(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(sinh(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_pow(JSObj::jsobj j1, JSObj::jsobj j2) {
    if (get_jotype(j1) != JSObj::jst_num || get_jotype(j2) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(pow(get_joval_dbl(j1), get_joval_dbl(j2)));
}
JSObj::jsobj jsf_Math_asinh(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(asinh(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_ceil(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(ceil(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_atan2(JSObj::jsobj j1, JSObj::jsobj j2) {
    if (get_jotype(j1) != JSObj::jst_num || get_jotype(j2) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atan2(get_joval_dbl(j1), get_joval_dbl(j2)));
}
JSObj::jsobj jsf_Math_asin(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(asin(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_atanh(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atanh(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_exp(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(exp(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_tan(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(tan(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_log(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(log(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_log10(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(log10(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_acos(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(acos(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_atan(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atan(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_tanh(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(tanh(get_joval_dbl(jo)));
}
JSObj::jsobj jsf_Math_sin(JSObj::jsobj jo) {
    if (get_jotype(jo) != JSObj::jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(sin(get_joval_dbl(jo)));
}

