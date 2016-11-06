/*
 * test-math.h
 * Author: Keith Stellyes
 * Test the Math built-in.
 * Implementing methods per:
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math
 */

#pragma once
#include "../../test-functions/assertions.h"

#include "../../misc.h"
#include "../../jsobj/js-obj.h"
#include "../../jsobj/js-obj-functions.h"
#include "../../jslibs/stdlib/math/math-functions.h"
#include "../largetext.h"

#include<stdbool.h>
#include<stdio.h>

#define josign_d(n) jsf_Math_sign(new_jsobj_dbl(n))
#define josign_str(s) jsf_Math_sign(new_jsobj_str(s))

void __test_random(assertparams) {
	jsobj jo1 = jsf_Math_random();
	jsobj jo2 = jsf_Math_random();
	*total += 1;
	if (jo1.val.d == jo2.val.d) {
		jo2 = jsf_Math_random();
		if (jo1.val.d == jo2.val.d) {
			printf("Math.random() equals self on subsequent runs:%f;%f\n",
					jo1.val.d, jo2.val.d);
			*fails += 1;
		}
	}
}

void __test_sign_num(assertparams) {
	jsobj jo = josign_d(-1);
	_asserteq_dbl("Math.sign(-1) failed", -1, jo.val.d);
	jo = josign_d(0);
	_asserteq_dbl("Math.sign(0) failed", 0, jo.val.d);
	jo = josign_d(1);
	_asserteq_dbl("Math.sign(1) failed", 1, jo.val.d);
	jo = josign_d(-.1);
	_asserteq_dbl("Math.sign(-.1) failed", -1, jo.val.d);
	jo = josign_d(.1);
	_asserteq_dbl("Math.sign(.1) failed", 1, jo.val.d);

}

void __test_sign_str(assertparams) {
#define test_for_nan(s) jo = josign_str(s); \
_asserteq_typ("Math.sign(somestring) failed", jst_nan, jo.type)

	jsobj jo = josign_str("-1");
	_asserteq_dbl("Math.sign(\"-1\") failed", -1, jo.val.d);
	jo = josign_str("0");
	_asserteq_dbl("Math.sign(\"0\") failed", 0, jo.val.d);
	jo = josign_str("1");
	_asserteq_dbl("Math.sign(\"1\") failed", 1, jo.val.d);

	jo = josign_str(" -1");
	_asserteq_dbl("Math.sign(\" -1\") failed", -1, jo.val.d);
	jo = josign_str(" 0");
	_asserteq_dbl("Math.sign(\" 0\") failed", 0, jo.val.d);
	jo = josign_str(" 1");
	_asserteq_dbl("Math.sign(\" 1\") failed", 1, jo.val.d);

	jo = josign_str(" -1 ");
	_asserteq_dbl("Math.sign(\" -1 \") failed", -1, jo.val.d);
	jo = josign_str(" 0 ");
	_asserteq_dbl("Math.sign(\" 0 \") failed", 0, jo.val.d);
	jo = josign_str(" 1 ");
	_asserteq_dbl("Math.sign(\" 1 \") failed", 1, jo.val.d);

	test_for_nan("a");
	test_for_nan(" a");
	test_for_nan("-");
	test_for_nan("a1");
	test_for_nan("-a");
	test_for_nan("");
	test_for_nan("apiojef9324j");
	test_for_nan("-1-");
	test_for_nan(".");
	test_for_nan("..");
	test_for_nan("1..");
	test_for_nan("1...");
	test_for_nan("-142.34.");

}

void do_stdlibtest_math(assertparams) {
	__test_random(total, fails);
	__test_sign_num(total, fails);
	__test_sign_str(total, fails);
}

#undef test_for_nan(s)
#undef josign_d(n)
