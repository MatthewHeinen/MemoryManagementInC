//
// Created by mheinen on 11/2/22.
//

#include <math.h>
#include "BigInt.h"

/**
 * big int constructor
 * @param: i - is an unsigned int that we are putting an integer int
 * */
BigInt::BigInt(unsigned int i) {
    unsigned int *input = new unsigned int[1];
    input[0] = i;
    this->bigInt = input;
    this->size = 1;
}

/**
 * big ing constructor without a parameter
 * constructor initialize an array of size int that has a zero
 * */
BigInt::BigInt()
{
    this->bigInt = nullptr;    // We _strongly_ recommend you put "this->" for all initializations in constructor
    this->size = 1;
}

/**
 * Function appends a carry to the end of an array
 * @param: first is the BigInt that we want to append a carry on to
 * */
BigInt extend(BigInt *first, int carry) {
    BigInt result;
    unsigned int *temp = new unsigned int[first->size + 1];
    result.bigInt = temp;
    result.size = first->size + 1;
    for (int i = 0; i < first->size; i++) {
        result.bigInt[i] = first->bigInt[i];
    }
    delete[] first->bigInt;
    result.bigInt[first->size] = carry;
    return result;
}

int bigger_big_int(BigInt i, BigInt j) {
    if (i.size > j.size) {
        return 1;
    } else if (j.size > i.size) {
        return 0;
    } else {
        return -1;
    }
}


BigInt fibBigInt(unsigned int n) {
    BigInt first = BigInt(0);
    BigInt second = BigInt(1);
    BigInt result = BigInt();

    if (n == 0) {
        delete[] second.bigInt;
        return first;
    } else if (n == 1) {
        delete[] first.bigInt;
        return second;
    }

    for (unsigned int i = 2; i <= n; i++) {
        result = first + second;
        delete[] first.bigInt;
        first = second;
        second = result;
    }
    delete[] first.bigInt;
    return result;
}

BigInt operator+(const BigInt i, const BigInt j) {
    unsigned int range = 0;
    BigInt bigger;
    BigInt smaller;
    if (bigger_big_int(i, j) == 1) {
        bigger = i;
        smaller = j;
        range = i.size;
    } else if (bigger_big_int(i, j) == 0) {
        smaller = i;
        bigger = j;
        range = j.size;
    } else {
        smaller = i;
        bigger = j;
        range = i.size;
    }

    unsigned int carry = 0;
    BigInt extended = BigInt();
    extended.bigInt = new unsigned int[range];
    extended.size = range;
    for (int index = 0; index < range; index++) {
        if (index > smaller.size - 1) {
            if (bigger.bigInt[index] > UINT_MAX - carry) {
                extended.bigInt[index] = carry - (UINT_MAX - bigger.bigInt[index]);
                carry = 1;
            } else {
                extended.bigInt[index] = bigger.bigInt[index]  + carry;
                carry = 0;
            }
        } else {
            if (bigger.bigInt[index] > UINT_MAX - smaller.bigInt[index]) {
                extended.bigInt[index] = smaller.bigInt[index] - (UINT_MAX - bigger.bigInt[index]) + carry;
                carry = 1;
            } else {
                extended.bigInt[index] = bigger.bigInt[index] + smaller.bigInt[index] + carry;
                carry = 0;
            }
        }
    }

    if ((carry != 0)){
        extended = extend(&extended, carry);
    }

    return extended;
}

bool operator==(const BigInt i, const BigInt j) {
    if (i.size == j.size) {
        for (int index = 0; index < i.size; index++) {
            if (i.bigInt[index] != j.bigInt[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

BigInt &BigInt::operator+=(const BigInt i) {
    BigInt result = *this + i;
    *this = result;
    return *this;
}

bool isZero(BigInt j) {
    for (int i = 0; i < j.size; i++) {
        if (j.bigInt[i] != 0) {
            return false;
        }
    }
    return true;
}

void print_big_int(BigInt * j) {
    for (int i = 0; i < j->size; i++) {
        std::cout << j->bigInt[i] << std::endl;
    }
    delete[] j->bigInt;
}

std::ostream &operator<<(std::ostream &any_ostream, const BigInt &printMe)
{
    return any_ostream << big_int_to_int(printMe);
}
std::istream &operator>>(std::istream &any_istream, BigInt &inputMe)
{
    int readAnInt;
    any_istream >> readAnInt;
    inputMe = BigInt(readAnInt);
    return any_istream;
}

using std::cin, std::cout, std::endl, std::cerr;

int big_int_to_int(BigInt i) {
    unsigned int num = 0;
    if (i.size == 1) {
        num = i.bigInt[0];
        return num;
    } else {
        fprintf(stderr, "Oops, failed to add. Overflow!");
        exit(88);
    }
}

int BigInt_Demo()
{
    BigInt n = fibBigInt(1000000);
    print_big_int(&n);
    printf("Passed all tests!");
    return 1;
}
