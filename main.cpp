//
// Created by davew on 10/12/21.
//
/**
 * This is the main for the doubleInt. I did this in C
 * @author Matthew Heinen
 * @date 10/31/2022
 * My partner was Justin Reed, collaborated with Abel Kelbessa for logic on how to do some of the functions (Not my partner)
 */

#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include <cstring>
//#include "SafeInt.h"
#include "safe_int_just_c.h"
#include "twice_greaters.h"
#include "String.h"
#include "doubleInt.h"

int main() {
    std::cout << "Hello, world" << std::endl;
//    twice_greater_demo_v1();

    double_int n = make_double_int(INT_MAX);
    double_int m = make_double_int(214);
    double_int z = add_double_int(n, m);
    // double_int_add_to(&n,m);
    double_int work = fibDouble(92);
    double_int_demo();

    // need to add calls to test suite and/or user interface to work with the code here
    // String_Demo();
    // Both of the following run until end-of-input, so just use one or the other
    //safe_int_demo();  /// this runs until crash, so we'll not make it to the next line :-(
    std::cout << "all done" << std::endl;
}

