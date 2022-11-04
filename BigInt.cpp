//
// Created by mheinen on 11/2/22.
//

#include <cstdlib>
#include "BigInt.h"

using namespace std;

#include <cmath>
#include <iostream>
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

void BigInt_Demo()
{

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
        if (i == 46) {
            std::cout<< fib[i].bigInt[0] << std::endl;
        }
        if (i == 47) {
            std::cout<< fib[i].bigInt[0] << std::endl;
        }
    }

    return fib[n];
}

BigInt add_to_nums(BigInt *i, BigInt *j) {
    unsigned int range = 0;
    unsigned int length = 0;
    if (bigger_big_int(i, j) == 1) {
        range = j->size;
    } else if (bigger_big_int(i, j) == 0) {
        range = i->size;
    } else {
        range = i->size;
    }

    BigInt extended = BigInt();
    extended.bigInt = new unsigned int[range + 1];
    extended.size = range;
    unsigned int carry = 0;
    BigInt *res;
    BigInt curr;

    for (unsigned int index = 0; index < range; index++) {
        if (((i->bigInt[index] > UINT_MAX - j->bigInt[index]) == 0) && (j->bigInt[index] > UINT_MAX - i->bigInt[index]) == 0) {
            if (carry > 0 && carry < UINT_MAX) {
                extended.bigInt[index] = i->bigInt[index] + j->bigInt[index] + carry;
                carry = 0;
            } else {
                extended.bigInt[index] = i->bigInt[index] + j->bigInt[index];
            }
        } else if ((i->bigInt[index] > UINT_MAX - j->bigInt[index]) || (j->bigInt[index] > UINT_MAX - i->bigInt[index])) {
            if (carry > 0 && (i->bigInt[index] > UINT_MAX - j->bigInt[index])) {
                extended.bigInt[index] = (UINT_MAX) - (UINT_MAX - i->bigInt[index]);
                carry += i->bigInt[index] - UINT_MAX + j->bigInt[index] + carry -1;
            } else if (carry > 0 && (j->bigInt[index] > UINT_MAX - i->bigInt[index]))  {
                extended.bigInt[index] = (UINT_MAX) - (UINT_MAX - j->bigInt[index]);
                carry += j->bigInt[index] - UINT_MAX + i->bigInt[index]-1;
            } else if (i->bigInt[index] > UINT_MAX - j->bigInt[index]) {
                extended.bigInt[index] = (UINT_MAX) - (UINT_MAX - i->bigInt[index]);
                carry += i->bigInt[index] - UINT_MAX + j->bigInt[index]-1;
            } else if (j->bigInt[index] > UINT_MAX - i->bigInt[index]) {
                extended.bigInt[index] = (UINT_MAX) - (UINT_MAX - j->bigInt[index]);
                carry += j->bigInt[index] - UINT_MAX + i->bigInt[index]-1;
            }
        }
    }

    /** 1 = UINT_MAX
     * i = [1, 1, 1, 1]
     * j = [1, 1]
     * res = [0, 0]
     * carry = 1
     * int i;
     * for (i = 0; i < length of shorter; i++)
     *    res = [0 , 0]
     * if (carry != 0 and i < length of longer)
     * for loop to add
     *    res = [0, 0, 0, 0]
     * extend should add the carry to the end
     *   res = [0, 0, 0, 0, 1]
     *  first big int = [999]
     * second big int = [10]
     * [1, 9]
     * 1009
     *
     * 4294967295
     * 10
     * [1, 9]
     * */

    //  std::cout<< carry << std::endl;
    if ((carry != 0)){
        curr = BigInt(carry);
        BigInt temp_res = BigInt();
        extended = fix(extended, curr);
    }

   for (int i = 0 ; i < extended.size; i++) {
       std::cout<< extended.bigInt[i] << std::endl;
       //std::cout<< extended.size << std::endl;
   }


    return extended;
}
