//
// Created by mheinen on 10/5/22.
//

#include "doubleInt.h"

#include <stdio.h>

void decimalToBinary(int num) {

    // Stores binary representation of number.
    int binaryNum[32]; // Assuming 32 bit integer.
    int i=0;

    for ( ;num > 0; ){
        binaryNum[i++] = num % 2;
        num /= 2;
    }

}