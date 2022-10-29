//
// Created by davew on 10/12/21.
//

#include <iostream>  // access to I.O. Streams library, for std::cout and std::endl
#include "SafeInt.h"
#include "safe_int_just_c.h"
#include "twice_greaters.h"
#include "String.h"
#include "doubleInt.h"

int main() {
    std::cout << "Hello, world" << std::endl;
    //twice_greater_demo_v1();

    double_int wack = double_fib(99);
    // need to add calls to test suite and/or user interface to work with the code here
    //String_Demo();
    // Both of the following run until end-of-input, so just use one or the other
    //safe_int_demo();  /// this runs until crash, so we'll not make it to the next line :-(
    std::cout << "all done" << std::endl;
}
