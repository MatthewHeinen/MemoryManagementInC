//
// Created by davew on 10/5/22.
//

#ifndef BIGINT_SAFE_INT_JUST_C_H
#define BIGINT_SAFE_INT_JUST_C_H

#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
extern "C" {
#endif


// A C data type is usually
//   * A "struct", which is basically a class with only data (no methods/functions) and all fields public
//   * A collection of functions that are the "approved" interface through which all work is done
// But, if somebody just ignores the approved-interface functions, they can make the data inconsistent :-(

#include <limits.h>

typedef int safe_int_base_type;  // make safe_int_base_type a synonym for "int"; we could change to "long long" :-)
#define SAFE_INT_MAX INT_MAX
#define SAFE_INT_MIN INT_MIN

typedef struct {
    safe_int_base_type theValue;
} safe_int;

safe_int make_safe_int(int i); // sort of like SafeInt(int i), but no type casting
// no need for SafeInt(), any C object can be created without initialization  =:-O

// Also, no control over casting or operators, including = because that's just not part of C
// So, instead, we just make a bucket of functions:

int make_int_from_safe_int(safe_int i);  // used to convert, since there's no cast operation

// substitutes for arithmetic operations:
safe_int add_safe_int(safe_int i, safe_int j);
safe_int *add_to_safe_int(safe_int *add_to_this_one, safe_int j);
safe_int div_safe_int(safe_int i, safe_int j);
safe_int *div_to_safe_int(safe_int *div_to_this_one, safe_int j);
double real_divide_safe_int(safe_int i, safe_int j);

#include <stdio.h>

int print_safe_int_to(FILE *destination, safe_int i);
int print_safe_int(safe_int i);  // to standard output, analogous to cout
// C uses 0 for false, 1 for true. We could "typedef int bool" and #define true and false, of course, but...
int read_safe_int(safe_int *read_my_value);  // return true if it succeeded

void safe_int_demo();

#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
}  // End of C/C++ bilingual code
#endif

#endif  // BIGINT_SAFE_INT_JUST_C_H
