//
// Created by mheinen on 10/5/22.
//

#include "doubleInt.h"
#include "safe_int_just_c.h"
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"

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
/**
 * max = 99
 * i = 51
 * j = 80
 * total = 131
 * ms = 1
 * ls = 31
 *
 * i.most = 1*INT_MAX
 * i.least = 1*INT_MAX
 * new range = i.most + i.least
 * 999
 * */

double_int add_double_int(double_int i, double_int j)
{
    double_int result;
    unsigned int i_ms;
    unsigned int i_ls;
    unsigned int j_ms;
    unsigned int j_ls;
    if ((i.leastSignificant > INT_MAX - j.leastSignificant || j.leastSignificant > INT_MAX - i.leastSignificant) || (i.mostSignificant > 0 || j.mostSignificant > 0)) {
        if ((j.leastSignificant > INT_MAX - i.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) {
            if (i.leastSignificant == INT_MAX) {
                i_ms = 1;
            } else {
                i_ms++;
            }
            i_ls = i.leastSignificant - INT_MAX;
            j_ms = 0;
            j_ls = j.leastSignificant;
            result.mostSignificant = i_ms + j_ms;
            result.leastSignificant = i_ls + j_ls;
            if (i_ls + j_ls == INT_MAX) {
                result.leastSignificant = i_ls + j_ls - 1;
            }
            return  result;
        } else if ((i.leastSignificant > INT_MAX - j.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) {
            i_ms = 0;
            i_ls = i.leastSignificant;
            if (j.leastSignificant == INT_MAX) {
                j_ms = 1;
            } else {
                j_ms++;
            }
            j_ls = j.leastSignificant - INT_MAX;
            result.mostSignificant = i_ms + j_ms;
            result.leastSignificant = i_ls + j_ls;
            if (i_ls + j_ls == INT_MAX) {
                result.leastSignificant = i_ls + j_ls - 1;
            }
            return  result;
        } else if (i.mostSignificant > 0 && j.mostSignificant > 0){
            result.mostSignificant = i.mostSignificant + j.mostSignificant;
            if (((j.leastSignificant > INT_MAX - i.leastSignificant) == 0) && ((i.leastSignificant > INT_MAX - j.leastSignificant) == 0)){
                result.leastSignificant = i.leastSignificant + j.leastSignificant;
            } else if (j.leastSignificant > INT_MAX - i.leastSignificant) {
                result.mostSignificant = i.mostSignificant + j.mostSignificant + 1;
                int temp = j.leastSignificant - INT_MAX;
                int temp2 = i.leastSignificant;
                result.leastSignificant = temp + temp2;
            } else if (i.leastSignificant > INT_MAX - j.leastSignificant) {
                result.mostSignificant = i.mostSignificant + j.mostSignificant + 1;
                int temp = i.leastSignificant - INT_MAX;
                int temp2 = j.leastSignificant;
                result.leastSignificant = temp + temp2;
            } else if (i.leastSignificant + j.leastSignificant == INT_MAX ) {
                result.mostSignificant++;
                result.leastSignificant = 0;
            }
            return result;
        }
    } else {
        unsigned int res = i.leastSignificant + j.leastSignificant;
        double_int no_overflow_result = make_double_int(res);
        return no_overflow_result;
    }

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

int fib(int n)
{
    int f[n+2];
    int i;

    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++)
    {
        f[i] = f[i-1] + f[i-2];
    }

    return f[n];
}

double_int fibDouble(unsigned int n)
{
    double_int f[n+2];
    f[0] = make_double_int(0);
    f[1] = make_double_int(1);

    for (int i = 2; i <= n; i++)
    {
        f[i] = add_double_int(f[i-1], f[i-2]);
    }

    return f[n];
}

int compare_double_int(double_int i, double_int j) {
    if (i.mostSignificant == j.mostSignificant && i.leastSignificant == j.leastSignificant) {
        printf("hi");
        return 1;
    } else {
        printf("bye");
        return 0;
    }
}

int double_int_demo() {
    double_int test;
    double_int fib1;
    double_int test1 = add_double_int(make_double_int(INT_MAX), make_double_int(214));
    test.mostSignificant = 1;
    test.leastSignificant = 214;
    assert(compare_double_int(test1, test) == 1);
    fib1.mostSignificant = 3511139102;
    fib1.leastSignificant = 859081435;
    assert(compare_double_int(fibDouble(92), fib1));
    printf("Passed all tests");
    return 1;
}
