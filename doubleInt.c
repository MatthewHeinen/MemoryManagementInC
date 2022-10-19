//
// Created by mheinen on 10/5/22.
//

#include "doubleInt.h"
#include "math.h"
#include <stdio.h>

void decimalToBinary(unsigned num) {

    // Stores binary representation of number.
    unsigned binaryNum[32]; // Assuming 32 bit integer.
    unsigned i=0;

    for ( ;num > 0; ){
        binaryNum[i++] = num % 2;
        num /= 2;
    }
}

void binaryToDecimal(unsigned num)
{
    int dec = 0, i = 0, rem;

    while (num!=0) {
        rem = num % 10;
        num /= 10;
        dec += rem * pow(2, i);
        i++;
    }
}

//Make array for both numbers
//split array in half to mimic what we did in lab
//Add function that will add array together and allow carry's
//Ensure carry goes from beginning part of array to end part of the array
//Get number out of array
//Throw error if there is an overflow. deal with in bigInt
