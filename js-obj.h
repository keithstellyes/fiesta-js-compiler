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
  */
#pragma once
#include<stdbool.h>
#include<time.h>
#include "js-string.h"

/* List incomplete */
typedef enum {
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
    jst_null
} jsobj_type;

typedef union {
    long long i;
    //char * s;
    jsstring s;
    double d;
    //jslist *;
    bool b;
    time_t tim;
} jsobj_val;

typedef struct {
    jsobj_type type;
    jsobj_val  val;
} jsobj;
