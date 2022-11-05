//
// Created by mheinen on 11/2/22.
//

#include <math.h>
#include "BigInt.h"

BigInt::BigInt(unsigned int i) {
    unsigned int *input = new unsigned int[1];
    input[0] = i;
    this->bigInt = input;    // We _strongly_ recommend you put "this->" for all initializations in constructor
    this->size = 1;
}

BigInt::BigInt()
{
    unsigned int *input = new unsigned int[1];
    input[0] = 0;
    this->bigInt = input;    // We _strongly_ recommend you put "this->" for all initializations in constructor
    this->size = 1;
}

BigInt * extend(BigInt * first, unsigned int first_size, BigInt * second, unsigned int second_size) {
    BigInt * arr = new BigInt[first_size + second_size];
    for(int i = 0; i < first_size; i++) {
        arr[i] = first[i];
    }
    //free(first);
    for (int j = 0; j < second_size; j++) {
        arr[j + first_size] = second[j];
    }
    return arr;
}

BigInt fix(BigInt first, BigInt carry) {
    BigInt result;
    unsigned int *temp = new unsigned int[first.size + 1];
    result.bigInt = temp;
    result.size = first.size + 1;
//    free(first);
    for (int i = 0; i < first.size; i++) {
        result.bigInt[i] = first.bigInt[i];
    }
    result.bigInt[first.size] = carry.bigInt[0];
    return result;
}

int bigger_big_int(BigInt *i, BigInt*j) {
    if (i->size > j->size) {
        return 1;
    } else if (j->size > i->size) {
        return 0;
    } else {
        return -1;
    }
}


BigInt fibBigInt(unsigned int n) {
    BigInt *fib = new BigInt[2];
    fib[0] = BigInt(0);
    fib[1] = BigInt(1);

    if (n == 0) { // fib 0
        return fib[0];
    } else if (n == 1) { // fib 1
        return fib[1];
    }
    for (unsigned int i = 2; i <= n; i++)
    {
        fib[i] = add_to_nums(&fib[i-1], &fib[i-2]);
    }

    return fib[n];
}

BigInt add_to_nums(BigInt *i, BigInt *j) {
    unsigned int range = 0;
    BigInt *bigger;
    BigInt *smaller;
    if (bigger_big_int(i, j) == 1) {
        bigger = i;
        smaller = j;
        range = i->size;
    } else if (bigger_big_int(i, j) == 0) {
        smaller = i;
        bigger = j;
        range = j->size;
    } else {
        smaller = i;
        bigger = j;
        range = i->size;
    }

    unsigned int carry = 0;
    BigInt extended = BigInt();
    extended.bigInt = new unsigned int[range];
    extended.size = range;
    for (int index = 0; index < range; index++) {
        if (index > smaller->size - 1) {
            if (bigger->bigInt[index] > UINT_MAX - carry) {
                extended.bigInt[index] = carry - (UINT_MAX - bigger->bigInt[index]);
                carry = 1;
            } else {
                extended.bigInt[index] = bigger->bigInt[index]  + carry;
                carry = 0;
            }
        } else {
            if (bigger->bigInt[index] > UINT_MAX - smaller->bigInt[index]) {
                extended.bigInt[index] = smaller->bigInt[index] - (UINT_MAX - bigger->bigInt[index]) + carry;
                carry = 1;
            } else {
                extended.bigInt[index] = bigger->bigInt[index] + smaller->bigInt[index] + carry;
                carry = 0;
            }
        }
    }

    if ((carry != 0)){
        BigInt curr;
        curr = BigInt(carry);
        extended = fix(extended, curr);
    }

    return extended;
}

void print_big_int(BigInt * j) {
    for (int i = 0; i < j->size; i++) {
        std::cout << j->bigInt[i] << std::endl;
    }
}

void BigInt_Demo()
{

}