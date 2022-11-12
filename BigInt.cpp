//
// Created by mheinen on 11/2/22.
//

#include <math.h>
#include "BigInt.h"
#include "logic.h"
#include "cstring"

/**
 * big int constructor
 * @param: i - is an unsigned int that we are putting an integer int
 * */
BigInt::BigInt(unsigned int i) {
    this->bigInt = new unsigned int[1];
    this->bigInt[0] = i;
    this->size = 1;
}

/**
 * big ing constructor without a parameter
 * constructor initialize an array of size int that has a zero
 * */
BigInt::BigInt()
{
    this->bigInt = nullptr;    // We _strongly_ recommend you put "this->" for all initializations in constructor
    this->size = 0;
}

//copy constructor
BigInt::BigInt(const BigInt &a){
    bigInt = new unsigned int[a.size];
    size = a.size;
    memcpy(bigInt, a.bigInt, sizeof(unsigned int) * a.size);

}

//destructor
BigInt::~BigInt() {delete [] this->bigInt;}


//= operator
BigInt& BigInt::operator=(const BigInt &a) {
    delete[] bigInt;
    bigInt= new unsigned int[a.size];
    memcpy(bigInt, a.bigInt, sizeof(unsigned int) * a.size);
    size = a.size;
    return *this;
}

//BigInt to string
std::string BigInt_to_String(BigInt *a){
    std::string ans = "";
    for(int i = a->size -1; i >= 0; i--){
        ans += std::to_string(int(a->bigInt[i]));
        if(i != 0) ans += ",";
    }
    return ans;

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
    if (i.size > j.size){
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
//        delete[] second.bigInt;
        return first;
    } else if (n == 1) {
//        delete[] first.bigInt;
        return second;
    }

    for (unsigned int i = 2; i <= n; i++) {
        result = first + second;
//        delete[] first.bigInt;
        first = second;
        second = result;
    }
//    delete[] first.bigInt;
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
//                delete[] i.bigInt;
//                delete[] j.bigInt;
                return false;
            }
        }
//        delete[] i.bigInt;
//        delete[] j.bigInt;
        return true;
    } else {
//        delete[] i.bigInt;
//        delete[] j.bigInt;
        return false;
    }
}

BigInt &BigInt::operator+=(const BigInt i) {
    BigInt result = *this + i;
//    delete [] i.bigInt;
//    delete[] this->bigInt;
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
//    delete[] j->bigInt;
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

unsigned int big_int_to_int(BigInt i) {
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
    BigInt one = BigInt(1);
    BigInt one_more = BigInt(one);
    std::cout << one << " and " << one_more << endl;


    /**
     *  == operator tests
     * */
    hccs_assert((fibBigInt(10) == fibBigInt(11)) == 0);
    hccs_assert((fibBigInt(100) == fibBigInt(99)) == 0);
//    hccs_assert((fibBigInt(29) == fibBigInt(29)) == 1);
//    hccs_assert((fibBigInt(40) == fibBigInt(40)) == 1);

    /**
     *     += operator tests
     * */
//    BigInt test1 = fibBigInt(10);
//    BigInt test2 = fibBigInt(11);
//    test1 += test2;
//    hccs_assert((fibBigInt(12) == test1) == 1);
//
//    BigInt test3 = fibBigInt(40);
//    BigInt test4 = fibBigInt(41);
//    test3 += test4;
//    hccs_assert((fibBigInt(42) == test3) == 1);
//
//    BigInt test5 = fibBigInt(150);
//    BigInt test6 = fibBigInt(151);
//    test5 += test6;
//    hccs_assert((fibBigInt(152) == test5) == 1);
//
//    BigInt test7 = fibBigInt(200);
//    BigInt test8 = fibBigInt(100);
//    test7 += test8;
//    hccs_assert((fibBigInt(300) == test7) == 0);

    /**
     * fib tests
     * */
//    BigInt test9 = fibBigInt(40);
//    BigInt test10 = BigInt(102334155);
//    hccs_assert((test9 == test10) == 1);
//
//    BigInt test11 = fibBigInt(47);
//    BigInt test12 = BigInt(2971215073);
//    hccs_assert((test11 == test12) == 1);
//
//    BigInt test13 = fibBigInt(30);
//    BigInt test14 = BigInt(832040);
//    hccs_assert((test13 == test14) == 1);
//
//    BigInt test15 = fibBigInt(30);
//    BigInt test16 = BigInt(75025);
//    hccs_assert((test15 == test16) == 0);
//
//    BigInt n = fibBigInt(10);
//    print_big_int(&n);
    printf("Passed all tests!");
    return 1;
}



