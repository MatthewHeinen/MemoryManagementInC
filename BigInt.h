//
// Created by mheinen on 11/2/22.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <iostream>
#include <climits>  // for, e.g., MAX_INT

typedef unsigned int BigIntBaseType;   // make safe_int_base_type a synonym for "int"; we could change to "long long" :-)
#define BIG_INT_MAX INT_MAX
#define BIG_INT_MIN INT_MIN

class BigInt {
public:         // Unlike Java, we don't have to say "public" and "private" on each member
    BigIntBaseType *bigInt;
    BigIntBaseType size;
    int bigger_big_int(BigInt *i, BigInt*j);

    BigInt(unsigned int i);             // initializes; also allows typecasting f int to SafeInt, see SafeInt demo
    BigInt();                  // this lets us create SafeInt without initialization
    BigInt * extend(BigInt * first, int first_size, BigInt * second, int second_size);

    explicit operator int() const;

private:

};

BigInt fibBigInt(unsigned int n);
BigInt add_to_nums(BigInt *i, BigInt *j);
BigInt fix(BigInt first, BigInt carry);
void BigInt_Demo();


#endif //BIGINT_BIGINT_H
