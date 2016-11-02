/*
 * misc.h
 * Author: Keith Stellyes
 * A header file for everything that doesn't belong anywhere else.
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define str(s) #s
#define ui64 uint_fast64_t
#define ui8 uint_fast8_t

// Taken from:
// http://stackoverflow.com/a/3643273/6913666

double rand_md()
{
    return (double)rand()/(RAND_MAX+1.0);
}
