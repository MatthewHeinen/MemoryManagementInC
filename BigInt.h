//
// Created by mheinen on 11/2/22.
//
#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <iostream>
#include <climits>  // for, e.g., MAX_INT
typedef unsigned int BigIntBaseType;
#define BIG_INT_MAX INT_MAX
#define BIG_INT_MIN INT_MIN

class BigInt {
public:

    explicit BigInt(unsigned int i);
    explicit BigInt();
    BigInt(const BigInt &a);
    ~BigInt();
    friend std::string BigInt_to_String(BigInt *a);
    BigInt& operator=(const BigInt &a);
    friend BigInt operator+(const BigInt i, const BigInt j);
    friend bool operator==(const BigInt i, const BigInt j);
    friend std::ostream &operator<<(std::ostream &any_ostream, const BigInt &printMe);
    friend std::istream &operator>>(std::istream &any_istream, BigInt &inputMe);
    BigInt &operator+=(const BigInt i);
    friend unsigned int big_int_to_int(BigInt i);
    friend void print_big_int(BigInt * i);
    friend bool isZero(BigInt i);
    friend int bigger_big_int(BigInt i, BigInt j);
    explicit operator int() const;


private:

    BigIntBaseType *bigInt;
    BigIntBaseType size;
    friend BigInt extend(BigInt *first, int carry);
};

int BigInt_Demo();
BigInt fibBigInt(unsigned int n);


#endif //BIGINT_BIGINT_H
