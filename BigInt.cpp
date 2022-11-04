//
// Created by mheinen on 11/2/22.
//

#include <cstdlib>
#include "BigInt.h"

using namespace std;

BigInt::BigInt(unsigned int i) {
    unsigned int *input = new unsigned int[1];
    input[0] = i;
    this-> bigInt = input;
    this->size = 1;

}

BigInt::BigInt()
{
    unsigned int *input = new unsigned int[1];
    input[0] = 0;
    this-> bigInt = input;
    this->size = 1;

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
    return arr;
}

BigInt * create(BigInt value, unsigned int count) {
    BigInt * arr = new BigInt[count];
    for(int i = 0; i < count; i++) {
        arr[i] = value;
    }
    return arr;
}

int find_bigger_big_int(BigInt *i, BigInt*j){

}

BigInt add_big_int(BigInt i, BigInt j) {

}



void BigInt_Demo()
{

}

