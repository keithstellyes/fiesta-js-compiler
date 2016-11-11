
/*
 * js-obj.h
 * Author: Keith Stellyes
 * The Object, the var, wow!
 */

/*
 * Javascript values can contain all kinds of things.
 * It may be a pointer to a string or a list, or a float,
 * or NaN... Unions will provide an elegant way of handling this.
 */
 
 /*
  * All JavaScript types:
  * Array
  * Boolean
  * Date
  * Error
  * Function
  * JSON
  * Math
  * Number
  * Object
  * RegExp
  * String
  * Map
  * Set
  * WeakMap
  * WeakSet
  
  * Note that while these are canonical definitions, some of these are written
  * as separate values in the jsobj_type enum. For example, in JavaScript, NaN
  * is considered to be of the type Number, but is a separate value in the enum.
  *
  * Conveniently, even though NaN is _technically_ of the type Number, it is in
  * fact more efficent to just store it as a separate type anyway, allowing for
  * Number.isFinite to be simply a one-line function. return jo.type == jst_num;
  */
#pragma once
#include<stdbool.h>
#include<time.h>
#include "js-func.h"
#include "../uthash/utstring.h"
#include "../uthash/uthash.h"
#include "js-arr.h"

namespace JSObj {
	struct jsfunc;
	union jsobj_val;
	//enum jsfunc_type;
	union jsf_ptr;
	struct jsobj;
	//enum jsobj_type;
	struct jsarr_el;

	enum jsfunc_type {
		jsfargc_indef,
		jsfargc_0,
		jsfargc_1,
		jsfargc_2,
		jsfargc_3,
	};

	/* List incomplete */
	enum jsobj_type{
		jst_num,
		jst_str,
		jst_set,
		jst_map,
		jst_bool,
		jst_undef,
		jst_nan,
		jst_pinf,
		jst_ninf,
		jst_regex,
		jst_arr,
		jst_obj,
		jst_null,
		jst_datetime
	};

	union jsf_ptr {
			jsobj (*jsfargp_indef)(int, jsobj*);
			jsobj (*jsfargp_0)(jsobj);
			jsobj (*jsfargp_1)(jsobj);
			jsobj (*jsfargp_2)(jsobj, jsobj);
			jsobj (*jsfargp_3)(jsobj, jsobj, jsobj);
	};

	struct jsfunc {
		jsfunc_type type;
		jsf_ptr ptr;
	};

	union jsobj_val {
		long long i;
		/* UT_STRING TO BE DEPRECATED */
		UT_string* s;
		double d;
		bool b;
		time_t tim;
		jsfunc funcptr;
		jsobj* arrhead;
	};


	struct jsobj {
		jsobj_type type;
		jsobj_val  val;
		jsobj* next;
		jsobj* prev;
		UT_hash_handle hh;
	};
};
