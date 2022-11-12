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
public: //these are all of our functions that are public for big int

    explicit BigInt(unsigned int i);
    explicit BigInt();
    BigInt(const BigInt &a);
    ~BigInt();
    BigInt& operator=(const BigInt &a);
    friend BigInt operator+(const BigInt &i, const BigInt &j);
    friend bool operator==(const BigInt i, const BigInt j);
    friend std::ostream &operator<<(std::ostream &any_ostream, const BigInt &printMe);
    friend std::istream &operator>>(std::istream &any_istream, BigInt &inputMe);
    BigInt &operator+=(const BigInt &i);
    friend unsigned int big_int_to_int(BigInt i);
    friend void print_big_int(BigInt * i);
    friend bool isZero(BigInt i);
    friend int bigger_big_int(BigInt i, BigInt j);
    void extend();
    //explicit operator int() const;


private: //our private functions for big int

    BigIntBaseType *bigInt;
    BigIntBaseType size;
    //friend BigInt extend(BigInt *first, int carry);
};

//Other functions that I used
int BigInt_Demo();
BigInt fibBigInt(unsigned int n);


#endif //BIGINT_BIGINT_H
