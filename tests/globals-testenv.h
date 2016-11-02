/*
 * globals-testenv.h
 * Author: Keith Stellyes
 *
 * These are various variables if we are building with __BUILDOP_TEST
 */

#pragma once
#ifdef __BUILDOP_TST

#define _JSSTDOUT_BUFFSIZE 4000
char* _JSSTDOUT;

void _flushjsstdout() {
	memset(_JSSTDOUT, 0, sizeof(char));
}

void _init_globals_testenv() {
	_JSSTDOUT = (char*) malloc(_JSSTDOUT_BUFFSIZE);
}


#endif
