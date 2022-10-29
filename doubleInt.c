//
// Created by mheinen on 10/5/22.
//

#include "doubleInt.h"
#include "assert.h"
#include "safe_int_just_c.h"
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

double_int make_double_int(unsigned int i)
{
    double_int result;
    result.mostSignificant = 0;
    result.leastSignificant = i;
    return result;
}

int make_int_from_double_int(double_int i)
{
    if (i.mostSignificant*INT_MAX > INT_MAX - i.leastSignificant) {
        fprintf(stderr, "Oops, failed due to overflow!");
        exit(88);
    } else {
        return i.mostSignificant * INT_MAX + i.leastSignificant; //TODO: overflow warning. Ask question
    }
}

double_int add_double_int(double_int i, double_int j)
{
    double_int result;
    if (i.leastSignificant > INT_MAX - j.leastSignificant || j.leastSignificant > INT_MAX - i.leastSignificant) {
        if (j.leastSignificant > INT_MAX - i.leastSignificant) {
            int i_ms = 0;
            int i_ls = i.leastSignificant;
            int j_ms = j_ms + 1;
            int j_ls = j.leastSignificant - INT_MAX;
            result.mostSignificant = i_ms + j_ms;
            result.leastSignificant = i_ls + j_ls;
            if (i_ls + j_ls == INT_MAX) {
                result.leastSignificant = i_ls + j_ls - 1;
            }
            return  result;
        } else if (i.leastSignificant > INT_MAX - j.leastSignificant) {
            int i_ms = i_ms + 1;
            int i_ls = i.leastSignificant - INT_MAX;
            int j_ms = 0;
            int j_ls = j.leastSignificant;
            result.mostSignificant = i_ms + j_ms;
            result.leastSignificant = i_ls + j_ls;
            if (i_ls + j_ls == INT_MAX) {
                result.leastSignificant = i_ls + j_ls - 1;
            }
            return  result;
        }
    } else {
        int res = i.leastSignificant + j.leastSignificant;
        double_int no_overflow_result = make_double_int(res);
        return no_overflow_result;
    }
    return result;
}

double_int double_int_add_to(double_int * i, double_int j) {
    if ((i->mostSignificant  > INT_MAX - 1 && j.mostSignificant > INT_MAX - 1 )) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else if ((i->mostSignificant > INT_MAX - 1 || j.mostSignificant > INT_MAX - 1) && (i->leastSignificant > INT_MAX - j.leastSignificant)) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else if (((i->mostSignificant == 0) && (j.mostSignificant == INT_MAX)) && (((i->leastSignificant > INT_MAX - j.leastSignificant)) || ((j.leastSignificant > INT_MAX - i->leastSignificant)))) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else if (((i->mostSignificant == INT_MAX) && (j.mostSignificant == 0)) && (((i->leastSignificant > INT_MAX - j.leastSignificant)) || ((j.leastSignificant > INT_MAX - i->leastSignificant)))) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else {
        *i =  add_double_int(*i, j);
        return *i;
    }
}

unsigned int fib(unsigned int num)
{

}

double_int double_fib(unsigned int num)
{
    double_int f[num+2];

    f[0] = make_double_int(0);
    f[1] = make_double_int(1);

    for (int i = 2; i <= num; i++)
    {
        f[i] = add_double_int(f[i-1], f[i-2]);

    }
    return f[num];
}

//TODO: Remember to do the add zero function
int double_int_demo() {

    return 1;
}
