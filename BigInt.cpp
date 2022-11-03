//
// Created by mheinen on 11/2/22.
//

#include <cstdlib>
#include "BigInt.h"

using namespace std;

BigInt::BigInt(unsigned int i) {
    this->theValue = i;    // We _strongly_ recommend you put "this->" for all initializations in constructor

}

BigInt::BigInt()
{
    // this->theValue = -666;
}

BigInt * extend(BigInt * first, unsigned int first_size, BigInt * second, unsigned int second_size) {
    BigInt * arr = new BigInt[first_size + second_size];
    for(int i = 0; i < first_size; i++){
        arr[i] = first[i];
    }
    free (first);
    for (int j = 0; j < second_size; j++) {
        arr[j + first_size] = second[j];
    }
}

BigInt * create(BigInt value, unsigned int count) {
    BigInt * arr = new BigInt[count];
    for(int i = 0; i < count; i++) {
        arr[i] = value;
    }
    return arr;
}

BigInt add_big_int(BigInt i, BigInt j) {

}

void BigInt_Demo()
{

}

