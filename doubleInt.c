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
    if ((i.leastSignificant > INT_MAX - j.leastSignificant || j.leastSignificant > INT_MAX - i.leastSignificant) || (i.mostSignificant > 0 || j.mostSignificant > 0)) {
        if ((j.leastSignificant > INT_MAX - i.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) {
            result.mostSignificant++;
            result.leastSignificant = i.leastSignificant - INT_MAX + j.leastSignificant;
            if (result.leastSignificant == INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1;
            }
            return  result;
        } else if ((i.leastSignificant > INT_MAX - j.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) {
            result.mostSignificant++;
            result.leastSignificant = i.leastSignificant + j.leastSignificant - INT_MAX;
            if (result.leastSignificant== INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1;
            }
            return  result;
        } else if (i.mostSignificant > 0 && j.mostSignificant > 0){
            if (i.mostSignificant == INT_MAX || j.mostSignificant == INT_MAX) {
                fprintf(stderr, "Oops, failed due to overflow!");
                exit(88);
            }
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
    if ((i->mostSignificant  > UINT_MAX - 1 && j.mostSignificant > UINT_MAX - 1 )) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else if ((i->mostSignificant > UINT_MAX - 1 || j.mostSignificant > UINT_MAX - 1) && (i->leastSignificant > UINT_MAX - j.leastSignificant)) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else if (((i->mostSignificant == 0) && (j.mostSignificant == UINT_MAX)) && (((i->leastSignificant > UINT_MAX - j.leastSignificant)) || ((j.leastSignificant > UINT_MAX - i->leastSignificant)))) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else if (((i->mostSignificant == UINT_MAX) && (j.mostSignificant == 0)) && (((i->leastSignificant > UINT_MAX - j.leastSignificant)) || ((j.leastSignificant > UINT_MAX - i->leastSignificant)))) {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    } else {
        *i =  add_helper_for_add_to(*i, j);
        return *i;
    }
}

double_int add_helper_for_add_to(double_int i, double_int j) {
    double_int result;
    if ((i.leastSignificant > INT_MAX - j.leastSignificant || j.leastSignificant > INT_MAX - i.leastSignificant) || (i.mostSignificant > 0 || j.mostSignificant > 0)) {
        if ((j.leastSignificant > INT_MAX - i.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) {
            result.mostSignificant = 1;
            result.leastSignificant = i.leastSignificant - INT_MAX + j.leastSignificant;
            if (result.leastSignificant == INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1;
            }
            return  result;
        } else if ((i.leastSignificant > INT_MAX - j.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) {
            result.mostSignificant = 1 ;
            result.leastSignificant = i.leastSignificant + j.leastSignificant - INT_MAX;
            if (result.leastSignificant== INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1;
            }
            return  result;
        } else if (i.mostSignificant > 0 && j.mostSignificant > 0){
            if (i.mostSignificant == INT_MAX || j.mostSignificant == INT_MAX) {
                fprintf(stderr, "Oops, failed due to overflow!");
                exit(88);
            }
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

int fib(int n)
{
    int f[n+2];
    int i;

    f[0] = 0;
    f[1] = 1;

    if (n == 0) {
        return f[0];
    } else if (n == 1) {
        return f[1];
    }

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

    if (n == 0) {
        return f[0];
    } else if (n == 1) {
        return f[1];
    }
    for (unsigned int i = 2; i <= n; i++)
    {
        f[i] = add_double_int(f[i-1], f[i-2]);
    }

    return f[n];
}

int zero_check(double_int n) {
    if (n.mostSignificant + n.leastSignificant == 0) {
        return 1;
    } else {
        return 0;
    }
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
    /**
     * Addition section
     * */
    // test 1
    double_int double_num1;
    double_int double_num2 = add_double_int(make_double_int(INT_MAX), make_double_int(214));
    double_num1.mostSignificant = 1;
    double_num1.leastSignificant = 214;
    assert(compare_double_int(double_num2, double_num1) == 1);
    //test 2
    double_int fib_num_47;
    fib_num_47.mostSignificant = 1;
    fib_num_47.leastSignificant = 823731426;
    double_int double_num4 = add_double_int(make_double_int(1134903170), make_double_int(1836311903));
    assert(compare_double_int(fib_num_47, double_num4) == 1);
    //test 3
    double_int fib_num_90;
    fib_num_90.mostSignificant = 1341135797;
    fib_num_90.leastSignificant = 1907004461;
    double_int fib_num_88;
    double_int fib_num_89;
    fib_num_88.mostSignificant = 512268291;
    fib_num_88.leastSignificant = 566964654;
    fib_num_89.mostSignificant = 828867506;
    fib_num_89.leastSignificant = 1340039807;
    double_int fib_num_88_plus_89 = add_double_int(fib_num_88, fib_num_89);
    assert(compare_double_int(fib_num_90, fib_num_88_plus_89) == 1);
    //test 4
    double_int fib_num_59;
    fib_num_59.mostSignificant = 445;
    fib_num_59.leastSignificant = 1091803126;
    double_int fib_num_57;
    double_int fib_num_58;
    fib_num_57.mostSignificant = 170;
    fib_num_57.leastSignificant = 363076172;
    fib_num_58.mostSignificant = 275;
    fib_num_58.leastSignificant = 728726954;
    double_int fib_num_57_plus_58 = add_double_int(fib_num_57, fib_num_58);
    assert(compare_double_int(fib_num_59, fib_num_57_plus_58) == 1);


    /**
     * Fib test
     * */
    //test 1
    double_int fib_92;
    fib_92.mostSignificant = 3511139102;
    fib_92.leastSignificant = 859081435;
    assert(compare_double_int(fibDouble(92), fib_92) == 1);

    //test 2
    double_int fib_47;
    fib_47.mostSignificant = 1;
    fib_47.leastSignificant = 823731426;
    assert(compare_double_int(fibDouble(47), fib_47) == 1);

    //test 3
    double_int fib_1;
    fib_1.mostSignificant = 0;
    fib_1.leastSignificant = 1;
    assert(compare_double_int(fibDouble(1), fib_1) == 1);

    /**
     * Add to tests
     * */
    //test 4
    double_int n = make_double_int(1);
    double_int m = make_double_int(1);
    double_int n_plus_m = double_int_add_to(&n,m);
    assert(compare_double_int(n, fibDouble(3)) == 1);

    //test 5
    double_int n1;
    double_int m1;
    n1.mostSignificant = 2;
    n1.leastSignificant = 512559682;
    m1.mostSignificant = 3;
    m1.leastSignificant = 1336291108;
    double_int n_plus_m1 = double_int_add_to(&n1,m1);
    assert(compare_double_int(n1, fibDouble(50)) == 1);

    //test 6
    double_int n2;
    double_int m2;
    n2.mostSignificant = 0;
    n2.leastSignificant = 1134903170;
    m2.mostSignificant = 0;
    m2.leastSignificant = 1836311903;
    double_int n_plus_m2 = double_int_add_to(&n2,m2);
    assert(compare_double_int(n2, fibDouble(47)) == 1);

    //test 7
    double_int n3;
    double_int m3;
    n3.mostSignificant = 1341135797;
    n3.leastSignificant = 1907004461;
    m3.mostSignificant = 2170003304;
    m3.leastSignificant = 1099560621;
    double_int n3_plus_m3 = double_int_add_to(&n3,m3);
    assert(compare_double_int(n3, fibDouble(92)) == 1);

    printf("Passed all tests");
    return 1;
}

