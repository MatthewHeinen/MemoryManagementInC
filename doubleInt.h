//
// Created by mheinen on 10/5/22.
//
#ifndef BIGINT_DOUBLE_INT_H
#define BIGINT_DOUBLE_INT_H


#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
extern "C" {
#endif
typedef int double_int_base_type;

typedef struct {
    double_int_base_type mostSignificant;
    double_int_base_type leastSignificant;
} double_int;

double_int make_double_int(unsigned int i);
double_int double_int_add_to(double_int * i, double_int j);
int make_int_from_double_int(double_int i);
double_int add_double_int(double_int i, double_int j);
unsigned int fib(unsigned int num);
void double_int_demo();
#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
}
#endif

#endif //BIGINT_DOUBLE_INT_H
