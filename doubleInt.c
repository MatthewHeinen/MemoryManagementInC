//
// Created by mheinen on 10/5/22.
//
/**
 * This file has all of my functions that I used for the doubleInt claSS
 */

#include "doubleInt.h"
#include "safe_int_just_c.h" //These are all the necessary imports needed for the file to work
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"

/**
 * This is our constructor that makes the double int type from an int
 * @param i  an unsigned integer
 * @return a new type double int
 */
double_int make_double_int(unsigned int i)
{
    double_int result;
    result.mostSignificant = 0; //creating a most significant section that counts the amount of wrap around of max int
    result.leastSignificant = i; //the current integer goes into here
    return result; //return result of most and least significant
}

/**
 * This function converts our double int type back to int
 * @param i a double int
 * @return an unsigned int
 */
unsigned int make_int_from_double_int(double_int i)
{
    if (i.mostSignificant*INT_MAX > INT_MAX - i.leastSignificant) {
        fprintf(stderr, "Oops, failed due to overflow!"); //can only return an int up to int max
        exit(88);
    } else {
        return i.mostSignificant * INT_MAX + i.leastSignificant; //return the int
    }
}

/**
 * This function is how we add two double int's together
 * @param i double int
 * @param j double int
 * @return the sum of the double ints
 */
double_int add_double_int(double_int i, double_int j)
{
    double_int result;
    if ((i.leastSignificant > INT_MAX - j.leastSignificant || j.leastSignificant > INT_MAX - i.leastSignificant) || (i.mostSignificant > 0 || j.mostSignificant > 0)) { //checks of there is overflow
        if ((j.leastSignificant > INT_MAX - i.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) { //the if statement for only the first wrap around. going form most significant of 0 to 1
            result.mostSignificant++; //increment most significant by 1
            result.leastSignificant = i.leastSignificant - INT_MAX + j.leastSignificant; //update least significant
            if (result.leastSignificant == INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1; //subtracting 1 for the wrap around
            }
            return  result;
        } else if ((i.leastSignificant > INT_MAX - j.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) { //Same logic as above just for j instead of i
            result.mostSignificant++;
            result.leastSignificant = i.leastSignificant + j.leastSignificant - INT_MAX;
            if (result.leastSignificant== INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1;
            }
            return  result;
        } else if (i.mostSignificant > 0 && j.mostSignificant > 0){ //case where both most significant are greater than 1
            if (i.mostSignificant == INT_MAX || j.mostSignificant == INT_MAX) {
                fprintf(stderr, "Oops, failed due to overflow!"); //We detect overflow
                exit(88);
            }
            result.mostSignificant = i.mostSignificant + j.mostSignificant; //adding the most significants together
            if (((j.leastSignificant > INT_MAX - i.leastSignificant) == 0) && ((i.leastSignificant > INT_MAX - j.leastSignificant) == 0)){ //if there is no overflow for the least signifcant
                result.leastSignificant = i.leastSignificant + j.leastSignificant; // add the two least significant values
            } else if (j.leastSignificant > INT_MAX - i.leastSignificant) { //then we do least significant addition causing a wrap around
                result.mostSignificant = i.mostSignificant + j.mostSignificant + 1; //add one to most significant
                int temp = j.leastSignificant - INT_MAX;
                int temp2 = i.leastSignificant;
                result.leastSignificant = temp + temp2; //updating the least signifcant
            } else if (i.leastSignificant > INT_MAX - j.leastSignificant) { //same logic but just for j instead of i
                result.mostSignificant = i.mostSignificant + j.mostSignificant + 1;
                int temp = i.leastSignificant - INT_MAX;
                int temp2 = j.leastSignificant;
                result.leastSignificant = temp + temp2;
            } else if (i.leastSignificant + j.leastSignificant == INT_MAX ) { //case where there is a wraparound and there is no value in the least significant
                result.mostSignificant++;
                result.leastSignificant = 0;
            }
            return result; //return the answer
        }
    } else {
        unsigned int res = i.leastSignificant + j.leastSignificant;
        double_int no_overflow_result = make_double_int(res); //checks that there is no overflow
        return no_overflow_result;
    }

}

/**
 * This function is an checker for overflow and updates the value of duouble int i
 * @param i pointer to double int
 * @param j double int
 * @return the sum of the double ints
 */
double_int double_int_add_to(double_int * i, double_int j) {
    if ((i->mostSignificant  > UINT_MAX - 1 && j.mostSignificant > UINT_MAX - 1 )) { //Everything is overflow checking
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
        *i =  add_helper_for_add_to(*i, j); //if it passes all the checks, add the numbers together
        return *i;
    }
}

/**
 * Helper function for the addition for the add to function. This was made because for some reason it was mixing up the fibonacci sequence and add to functions. However, seperated they are good. Variable initilization issues
 * @param i double int
 * @param j double int
 * @return the sum of the double ints
 */
double_int add_helper_for_add_to(double_int i, double_int j) {
    double_int result;
    if ((i.leastSignificant > INT_MAX - j.leastSignificant || j.leastSignificant > INT_MAX - i.leastSignificant) || (i.mostSignificant > 0 || j.mostSignificant > 0)) { //checks of there is overflow
        if ((j.leastSignificant > INT_MAX - i.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) { //the if statement for only the first wrap around. going form most significant of 0 to 1
            result.mostSignificant = 1; //increment most significant by 1
            result.leastSignificant = i.leastSignificant - INT_MAX + j.leastSignificant; //update least significant
            if (result.leastSignificant == INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1; //subtracting 1 for the wrap around
            }
            return  result;
        } else if ((i.leastSignificant > INT_MAX - j.leastSignificant) && ((i.mostSignificant > 0 && j.mostSignificant > 0) == 0)) { //Same logic as above just for j instead of i
            result.mostSignificant = 1 ;
            result.leastSignificant = i.leastSignificant + j.leastSignificant - INT_MAX;
            if (result.leastSignificant== INT_MAX) {
                result.leastSignificant = result.leastSignificant - 1;
            }
            return  result;
        } else if (i.mostSignificant > 0 && j.mostSignificant > 0){ //case where both most significant are greater than 1
            if (i.mostSignificant == INT_MAX || j.mostSignificant == INT_MAX) {
                fprintf(stderr, "Oops, failed due to overflow!"); //We detect overflow
                exit(88);
            }
            result.mostSignificant = i.mostSignificant + j.mostSignificant; //adding the most significants together
            if (((j.leastSignificant > INT_MAX - i.leastSignificant) == 0) && ((i.leastSignificant > INT_MAX - j.leastSignificant) == 0)){ //if there is no overflow for the least signifcant
                result.leastSignificant = i.leastSignificant + j.leastSignificant; // add the two least significant values
            } else if (j.leastSignificant > INT_MAX - i.leastSignificant) { //then we do least significant addition causing a wrap around
                result.mostSignificant = i.mostSignificant + j.mostSignificant + 1; //add one to most significant
                int temp = j.leastSignificant - INT_MAX;
                int temp2 = i.leastSignificant;
                result.leastSignificant = temp + temp2; //updating least significant
            } else if (i.leastSignificant > INT_MAX - j.leastSignificant) { //same logic but just for j instead of i
                result.mostSignificant = i.mostSignificant + j.mostSignificant + 1;
                int temp = i.leastSignificant - INT_MAX;
                int temp2 = j.leastSignificant;
                result.leastSignificant = temp + temp2;
            } else if (i.leastSignificant + j.leastSignificant == INT_MAX ) { //case where there is a wraparound and there is no value in the least significant
                result.mostSignificant++;
                result.leastSignificant = 0;
            }
            return result;  //return the answer
        }
    } else {
        unsigned int res = i.leastSignificant + j.leastSignificant;
        double_int no_overflow_result = make_double_int(res); //checks that there is no overflow
        return no_overflow_result;
    }
}

/**
 * This is a function for the fibonacci sequence
 * @param n integer
 * @return the answer of that number in the sequence
 */
unsigned int fib(int n)
{
    int f[n+2];
    int i;

    f[0] = 0; //edge case
    f[1] = 1; //edge case

    if (n == 0) {
        return f[0]; //edge case
    } else if (n == 1) {
        return f[1]; //edge case
    }

    for (i = 2; i <= n; i++)
    {
        f[i] = f[i-1] + f[i-2]; //doing the fibonacci sequence
    }

    return f[n];
}

/**
 * This is a function for the fibonacci sequence using double int
 * @param n is an unsigned integer
 * @return the answer of that specific number in the sequence
 */
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
        f[i] = add_double_int(f[i-1], f[i-2]); //same logic as regular fib function, just updated for double int
    }

    return f[n];
}

/**
 * This function checks if the double int is equal to zero
 * @param n double int
 * @return either a 1 (true) if it is zero or a 0 (false) if it isn't
 */
int zero_check(double_int n) {
    if (n.mostSignificant + n.leastSignificant == 0) { //if the sum is zero
        return 1; //true
    } else {
        return 0;
    }
}

/**
 * Function that compares if the double ints most and least significants are equal
 * @param i double int
 * @param j double int
 * @return either a 1 (true) if it is zero or a 0 (false) if it isn't
 */
int compare_double_int(double_int i, double_int j) {
    if (i.mostSignificant == j.mostSignificant && i.leastSignificant == j.leastSignificant) { //If the most and least significant are equal
        return 1; //return true
    } else {
        return 0;
    }
}

/**
 * A function that prints double int to file
 * @param destination File
 * @param i double int
 * @return No return
 */
unsigned int print_double_int_to(FILE *destination, double_int i)
{
    fprintf(destination, "%u most significant \n", i.mostSignificant); //logic taken from safeInt
    fprintf(destination, "%u least significant \n", i.leastSignificant);
}

/**
 * Function that prints double int
 * @param i double int
 * @return None, prints
 */
unsigned int print_double_int(double_int i)
{
    return print_double_int_to(stdout, i);
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

    double_int fib_70;
    fib_70.mostSignificant = 88658;
    fib_70.leastSignificant = 5;
    assert(compare_double_int(fibDouble(70), fib_70) == 0);

    /**
     * Double int add to tests
     * */
    //test 1
    double_int n = make_double_int(1);
    double_int m = make_double_int(1);
    double_int n_plus_m = double_int_add_to(&n,m);
    assert(compare_double_int(n, fibDouble(3)) == 1);

    //test 2
    double_int n1;
    double_int m1;
    n1.mostSignificant = 2;
    n1.leastSignificant = 512559682;
    m1.mostSignificant = 3;
    m1.leastSignificant = 1336291108;
    double_int n_plus_m1 = double_int_add_to(&n1,m1);
    assert(compare_double_int(n1, fibDouble(50)) == 1);

    //test 3
    double_int n2;
    double_int m2;
    n2.mostSignificant = 0;
    n2.leastSignificant = 1134903170;
    m2.mostSignificant = 0;
    m2.leastSignificant = 1836311903;
    double_int n_plus_m2 = double_int_add_to(&n2,m2);
    assert(compare_double_int(n2, fibDouble(47)) == 1);

    //test 4
    double_int n3;
    double_int m3;
    n3.mostSignificant = 1341135797;
    n3.leastSignificant = 1907004461;
    m3.mostSignificant = 2170003304;
    m3.leastSignificant = 1099560621;
    double_int n3_plus_m3 = double_int_add_to(&n3,m3);
    assert(compare_double_int(n3, fibDouble(92)) == 1);

    /**
     * make int from double int tests
     * */

    double_int test33 = fibDouble(6);
    assert(make_int_from_double_int(test33) == 8);

    double_int test34 = fibDouble(18);
    assert(make_int_from_double_int(test34) == 2584);

    double_int test35 = fibDouble(37);
    assert(make_int_from_double_int(test35) == 24157817);

    /**
     * Tests to check the zero function
     * */

    double_int zero = make_double_int(0);
    assert(zero_check(zero) == 1);

    double_int one = make_double_int(1);
    assert(zero_check(one) == 0);

    /**
     * Tests to check the print capability. These print in the console
     * */

    print_double_int(test34);
    print_double_int(fib_92);

    printf("Passed all tests \n");
    return 1;
}

