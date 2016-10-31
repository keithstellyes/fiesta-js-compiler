/*
 * js-string.h
 * Author: Keith Stellyes
 * A basic datatype for a string. It manages growth of its own memory.
 */

#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/* The exact goldilocks amount for this I am unsure of. */
#define STRCHUNK 1000
#define ui64 uint_fast64_t

typedef struct jsstring {
    char * s;
    ui64 arrlen;
	ui64 total_chars;
} jsstring;

ui64 space_left_in_jsstring(jsstring jss) {
	return jss.arrlen - jss.total_chars;
}

jsstring new_jsstring(char * s) {
	ui64 charcount = strlen(s);
	jsstring jss;

	jss.arrlen = 0;
	while (jss.arrlen < charcount) {
		jss.arrlen += STRCHUNK;
	}

	jss.total_chars = charcount;
	jss.s = calloc(jss.arrlen, sizeof(char));
	strcpy(jss.s, s);
	return jss;
}

void append_to_jsstring(jsstring * dest, char * src) {
	ui64 srclen = strlen(src);
	if(space_left_in_jsstring(*dest) + srclen > dest->arrlen) {
		ui64 new_len = dest->arrlen;
		while(space_left_in_jsstring(*dest) + srclen > new_len) {
			new_len += STRCHUNK;
		}
		dest->s = realloc(dest->s, new_len);
		dest->arrlen = new_len;
	}
	strcat(dest->s, src);
	dest->total_chars += srclen;
}
