//
// Created by mheinen on 11/2/22.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

typedef unsigned int BigIntBaseType;   // make safe_int_base_type a synonym for "int"; we could change to "long long" :-)
#define SAFE_INT_MAX INT_MAX
#define SAFE_INT_MIN INT_MIN

class BigInt {
public:         // Unlike Java, we don't have to say "public" and "private" on each member

    BigInt(unsigned int i);             // initializes; also allows typecasting f int to SafeInt, see SafeInt demo
    BigInt();

private:        // Stuff below this line is private, i.e., only for methods ("member functions") and friend functions
    BigIntBaseType *bigInt;
    BigIntBaseType size;

};

void BigInt_Demo();
BigInt * create(BigInt value, unsigned int count);
BigInt * extend(BigInt * first, unsigned int first_size, BigInt * second, unsigned int second_size);

#endif //BIGINT_BIGINT_H