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

jsobj jsf_Math_sign(jsobj jo) {
	if(get_jotype(jo) == jst_num) {
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
	else if(get_jotype(jo) == jst_ninf) {
		return new_jsobj_dbl(-1);
	}
	else if(get_jotype(jo) == jst_pinf) {
		return new_jsobj_dbl(1);
	}
	else if(get_jotype(jo) == jst_null) {
		return new_jsobj_dbl(0);
	}
	else if(get_jotype(jo) == jst_str) {
		return jsf_Math_sign(jsobj_str_to_dbl(jo));
	}
	return new_jsobj_bytype(jst_nan);
}

jsobj jsf_Math_random() {
	return new_jsobj_dbl(rand_md());
}

jsobj jsf_Math_sinh(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(sinh(get_joval_dbl(jo)));
}
jsobj jsf_Math_pow(jsobj j1, jsobj j2) {
    if (get_jotype(j1) != jst_num || get_jotype(j2) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(pow(get_joval_dbl(j1), get_joval_dbl(j2)));
}
jsobj jsf_Math_asinh(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(asinh(get_joval_dbl(jo)));
}
jsobj jsf_Math_ceil(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(ceil(get_joval_dbl(jo)));
}
jsobj jsf_Math_atan2(jsobj j1, jsobj j2) {
    if (get_jotype(j1) != jst_num || get_jotype(j2) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atan2(get_joval_dbl(j1), get_joval_dbl(j2)));
}
jsobj jsf_Math_asin(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(asin(get_joval_dbl(jo)));
}
jsobj jsf_Math_atanh(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atanh(get_joval_dbl(jo)));
}
jsobj jsf_Math_exp(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(exp(get_joval_dbl(jo)));
}
jsobj jsf_Math_tan(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(tan(get_joval_dbl(jo)));
}
jsobj jsf_Math_log(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(log(get_joval_dbl(jo)));
}
jsobj jsf_Math_log10(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(log10(get_joval_dbl(jo)));
}
jsobj jsf_Math_acos(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(acos(get_joval_dbl(jo)));
}
jsobj jsf_Math_atan(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(atan(get_joval_dbl(jo)));
}
jsobj jsf_Math_tanh(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(tanh(get_joval_dbl(jo)));
}
jsobj jsf_Math_sin(jsobj jo) {
    if (get_jotype(jo) != jst_num) {
        return new_jsobj_nan();
    }
    return new_jsobj_dbl(sin(get_joval_dbl(jo)));
}

