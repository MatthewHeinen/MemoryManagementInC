//
// Created by mheinen on 10/5/22.
//
/**
 * This is my header file that stores all of my functions, struct  and the base type
 */
#ifndef BIGINT_DOUBLE_INT_H
#define BIGINT_DOUBLE_INT_H


#include <bits/types/FILE.h>

#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
extern "C" {
#endif
typedef unsigned int double_int_base_type;

typedef struct {
    double_int_base_type mostSignificant;
    double_int_base_type leastSignificant;
} double_int;

double_int make_double_int(unsigned int i);
double_int add_helper_for_add_to(double_int i, double_int j);
unsigned int print_double_int_to(FILE *destination, double_int i);
unsigned int print_double_int(double_int i);
double_int double_int_add_to(double_int * i, double_int j);
unsigned int make_int_from_double_int(double_int i);
double_int fibDouble(unsigned int n);
int zero_check(double_int n);
unsigned int fib(int n);
int compare_double_int(double_int i, double_int j);
double_int add_double_int(double_int i, double_int j);
int double_int_demo();
#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
}
#endif

#endif //BIGINT_DOUBLE_INT_H
