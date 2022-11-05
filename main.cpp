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
#include "BigInt.h"

/**
 * This is the main for the project. I did it in C programming language.
 * Partner: Adiel
 * Also worked with: Matt Heinen
 * */
int main() {
    std::cout << "Hello, world" << std::endl;


    BigInt z = BigInt();
    z.bigInt = new unsigned int[2];
    z.bigInt[0] = 4294967295;
    z.bigInt[1] = UINT_MAX-1;
    z.size = 2;
    BigInt c = BigInt();
    c.bigInt = new unsigned int[2];
    c.bigInt[0] = 4294967295;
    c.bigInt[1] = 512559681;
    c.size = 2;
    //[carry, ]

    BigInt n = fibBigInt(100000);
    print_big_int(&n);

}


