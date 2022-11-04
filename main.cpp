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

int main() {
    std::cout << "Hello, world" << std::endl;


    BigInt z = BigInt();
    z.bigInt = new unsigned int[3];
    z.bigInt[0] = UINT_MAX; // UINT_MAX ones = UINT_MAX*UINT_MAX
    z.bigInt[1] = 2;
    z.size = 2;
    BigInt c = BigInt();
    c.bigInt[0] = 2;
    c.bigInt[1] = 20;
    c.size = 2;
    // [1, 23]
    BigInt u = add_to_nums(&c, &z);
    // [Max, 5]
    //[max]
//    BigInt n = fibBigInt(47);
//    std::cout << "\nall done" << std::endl;
}

