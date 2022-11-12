//
// Created by mheinen on 11/2/22.
//
/**
 * This file contains all of our functions for the big int class
 */

#include <math.h>
#include "BigInt.h" //These are the libraries that I used for this lab
#include "logic.h"
#include "cstring"

/**
 * This is a constructor that intitializes the array
 * @param i is an unsigned int
 */
BigInt::BigInt(unsigned int i) {
    this->bigInt = new unsigned int[1];
    this->bigInt[0] = i; //setting i to the 1st element in the big int list
    this->size = 1; //size of the list is 1
}

/**
 * Constructor that creates a null big int type
 */
BigInt::BigInt()
{
    this->bigInt = nullptr;    //setting big int to null pointer
    this->size = 0; //therefore the size is 0
}

/**
 * This is a copy constructor that is used to help us ensure we don't double free anything. This is done with memcpy
 * @param a is of Big Int type
 */
BigInt::BigInt(const BigInt &a){
    bigInt = new unsigned int[a.size]; //big int can be of size a
    size = a.size;
    memcpy(bigInt, a.bigInt, sizeof(unsigned int) * a.size); //mem copy big int so that a double free can't take place

}

/**
 * This is our destrucotr that deletes all of our items when we are done with them
 */
BigInt::~BigInt() {delete [] this->bigInt;} //as it can be seen we are using the delete [] because its an array


/**
 * This operator assigns big int values and ensures we don't have any double frees
 * @param a is of big int type
 * @return the current big int
 */
BigInt& BigInt::operator=(const BigInt &a) {
    delete[] bigInt; //first delete
    bigInt= new unsigned int[a.size]; //create a new unsigned int array
    memcpy(bigInt, a.bigInt, sizeof(unsigned int) * a.size); //do a mem copy to ensure we don't double delete
    size = a.size;
    return *this; //this is signifying the current big int
}


/**
 * This is our method that extends our array if there is a carry
 */
void BigInt::extend(){
    unsigned int* temp = new unsigned int[this->size + 1]; //increasing size by 1
    for( int i = 0; i < this->size; i++){
        temp[i] = this->bigInt[i]; //lopping through the current big int
    }
    temp[this->size] = 1;
    this->size += 1; //increment size by 1
    delete [] (*this).bigInt; //delete the "garbage" that we created
    this->bigInt = temp;
}

/**
 * This method find the larger big int which is used in the add function
 * @param i is of big int type
 * @param j is of big int type
 * @return a 1 or 0 that basically signifies which one is larger
 */
int bigger_big_int(BigInt i, BigInt j) {
    if (i.size > j.size){
        return 1; //1 signifies i is greater
    } else if (j.size > i.size) {
        return 0; //0 signifies j is greater
    } else {
        return -1; //if they're equal return -1
    }
}

/**
 * This is our function that find numbers in the fibonacci sequence for big int
 * @param n unsigned int
 * @return the answer to the desired number in the fibonacci sequence
 */
BigInt fibBigInt(unsigned int n) {
    BigInt first = BigInt(0); //first is equal to big int 0
    BigInt second = BigInt(1); //second is equal to big int 1. these are base cases
    BigInt result = BigInt(); //otherwise, result is just big int

    if (n == 0) {
//        delete[] second.bigInt;
        return first; //base case
    } else if (n == 1) {
//        delete[] first.bigInt;
        return second; //base case
    }

    for (unsigned int i = 2; i <= n; i++) { //loop that calculates the correct answer for the fibonacci sequence
        result = first + second;
//        delete[] first.bigInt;
        first = second;
        second = result;
    }
//    delete[] first.bigInt;
    return result;
}

/**
 * This is our add function that adds together two big ints
 * @param i is a big int
 * @param j is a big int
 * @return the answer of the two added numbers
 */
BigInt operator+(const BigInt &i, const BigInt &j) {
    unsigned int range = 0;
    BigInt bigger; //initializing variables
    BigInt smaller;
    if (bigger_big_int(i, j) == 1) { //going back to our bigger big int function
        bigger = i;
        smaller = j; //logic from the bigger big int function
        range = i.size;
    } else if (bigger_big_int(i, j) == 0) {
        smaller = i;
        bigger = j;
        range = j.size; //logic from the bigger big int function
    } else {
        smaller = i;
        bigger = j;
        range = i.size; //logic from the bigger big int function
    }

    unsigned int carry = 0;
    BigInt extended = BigInt();
    extended.bigInt = new unsigned int[range];
    extended.size = range;
    for (int index = 0; index < range; index++) {
        if (index > smaller.size - 1) { //we are done with the smaller array
            if (bigger.bigInt[index] > UINT_MAX - carry) { //if there  is an overflow
                extended.bigInt[index] = carry - (UINT_MAX - bigger.bigInt[index]); //subtract a UINT max
                carry = 1; //add 1 to carry
            } else {
                extended.bigInt[index] = bigger.bigInt[index]  + carry; //otherwise there is no carry
                carry = 0;
            }
        } else {
            if (bigger.bigInt[index] > UINT_MAX - smaller.bigInt[index]) { //if there  is an overflow
                extended.bigInt[index] = smaller.bigInt[index] - (UINT_MAX - bigger.bigInt[index]) + carry; //subtract a UINT max
                carry = 1; //add 1 to carry
            } else {
                extended.bigInt[index] = bigger.bigInt[index] + smaller.bigInt[index] + carry; //the size of array is equal to the sum of the sizes of bigger and smaller
                carry = 0;
            }
        }
    }

    if ((carry != 0)){ //if there is a carry
        extended.extend(); //extend our array if big int type extended
    }

    return extended;
}

/**
 * This function checks if two big ints are equal to each other
 * @param i is a big int
 * @param j is a big int
 * @return a true for if they are equal and a false if they aren't
 */
bool operator==(const BigInt i, const BigInt j) {
    if (i.size == j.size) { //if the sizes of the arrays are equal
        for (int index = 0; index < i.size; index++) { //check each index of each array
            if (i.bigInt[index] != j.bigInt[index]) { //for the case that each index isn't equal
//                delete[] i.bigInt;
//                delete[] j.bigInt;
                return false;
            }
        }
//        delete[] i.bigInt;
//        delete[] j.bigInt;
        return true; //otherwise they were equal
    } else {
//        delete[] i.bigInt;
//        delete[] j.bigInt;
        return false; //if the sizes were unequal at the start we can just return false
    }
}

/**
 * This function adds a big int to an already existing big int
 * @param i is a big int
 * @return the sum of the two big ints
 */
BigInt &BigInt::operator+=(const BigInt &i) {
    BigInt result = *this + i; //result is the previous sum and this new big int
//    delete [] i.bigInt;
//    delete[] this->bigInt;
    *this = result; //set this equal to result
    return *this;
}

/**
 * Checks if a big int is equal to 0
 * @param j is a big int
 * @return
 */
bool isZero(BigInt j) {
    for (int i = 0; i < j.size; i++) { //for the length of the big int list
        if (j.bigInt[i] != 0) { //if an element isn't 0 its false
            return false;
        }
    }
    return true; //otherwise everything was 0
}

/**
 * This function prints each index of the big int array. We print the most leat significant number at the top and then more significant going down
 * Therefore it goes number, num*UINT_Max, num*UINT_Max^2 etc.
 * @param j is a big int
 */
void print_big_int(BigInt * j) {
    for (int i = 0; i < j->size; i++) { //for the length of the big int array
        std::cout << j->bigInt[i] << std::endl; //print it's value
    }
//    delete[] j->bigInt;
}


std::ostream &operator<<(std::ostream &any_ostream, const BigInt &printMe) //is used to print. Dave told us put this line in. I think its from safe int but maybe big string
{
    return any_ostream << big_int_to_int(printMe);

}
std::istream &operator>>(std::istream &any_istream, BigInt &inputMe) //used for inputs. Dave told me to put this in as well. I think its from safe int but maybe big string
{
    int readAnInt;
    any_istream >> readAnInt;
    inputMe = BigInt(readAnInt);
    return any_istream;
}

using std::cin, std::cout, std::endl, std::cerr; //allows us to print using cout and endl

/**
 * This converts our big int type into an integer
 * @param i is a big int
 * @return an integer
 */
unsigned int big_int_to_int(BigInt i) {
    unsigned int num = 0;
    if (i.size == 1) { //if the size of the big int array is 1, this means it is less than UINT MAX so we can print it
        num = i.bigInt[0];
        return num;
    } else {
        fprintf(stderr, "Oops, failed to add. Overflow!"); //otherwise it overflows
        exit(88);
    }
}

int BigInt_Demo()
{
    /**
     * Dave's test
     */
    BigInt one = BigInt(1);
    BigInt one_more = BigInt(one);
    std::cout << one << " and " << one_more << endl;

    /**
     * zero tests
     */

    hccs_assert(isZero(one_more) == 0);
    hccs_assert(isZero(BigInt(0)) == 1);

    /**
     * Addition tests
     */
    BigInt add = BigInt(100) + BigInt(75);
    hccs_assert(add == BigInt(175));

    BigInt add1 = BigInt(99) + BigInt(1);
    hccs_assert(add1 == BigInt(100));

    BigInt add2 = fibBigInt(55) + fibBigInt(56);
    hccs_assert(add2 == fibBigInt(57));

    /**
     *  == operator tests
     * */
    hccs_assert((fibBigInt(10) == fibBigInt(11)) == 0);
    hccs_assert((fibBigInt(100) == fibBigInt(99)) == 0);
    hccs_assert((fibBigInt(29) == fibBigInt(29)) == 1);
    hccs_assert((fibBigInt(40) == fibBigInt(40)) == 1);

    /**
     *     += operator tests
     * */
    BigInt test1 = fibBigInt(10);
    BigInt test2 = fibBigInt(11);
    test1 += test2;
    hccs_assert((fibBigInt(12) == test1) == 1);

    BigInt test3 = fibBigInt(40);
    BigInt test4 = fibBigInt(41);
    test3 += test4;
    hccs_assert((fibBigInt(42) == test3) == 1);

    BigInt test5 = fibBigInt(150);
    BigInt test6 = fibBigInt(151);
    test5 += test6;
    hccs_assert((fibBigInt(152) == test5) == 1);

    BigInt test7 = fibBigInt(200);
    BigInt test8 = fibBigInt(100);
    test7 += test8;
    hccs_assert((fibBigInt(300) == test7) == 0);

    /**
     * fib tests
     * */
    BigInt test9 = fibBigInt(40);
    BigInt test10 = BigInt(102334155);
    hccs_assert((test9 == test10) == 1);

    BigInt test11 = fibBigInt(47);
    BigInt test12 = BigInt(2971215073);
    hccs_assert((test11 == test12) == 1);

    BigInt test13 = fibBigInt(30);
    BigInt test14 = BigInt(832040);
    hccs_assert((test13 == test14) == 1);

    BigInt test15 = fibBigInt(30);
    BigInt test16 = BigInt(75025);
    hccs_assert((test15 == test16) == 0);

    /**
     * big int to int
     */
    BigInt test_int = BigInt(6);
    hccs_assert(big_int_to_int(test_int) == 6);

    BigInt test_int1 = fibBigInt(35);
    hccs_assert(big_int_to_int(test_int1) == 9227465);

    /**
     * fib 1 million
     */
    BigInt n = fibBigInt(10000);
    print_big_int(&n);
    printf("Passed all tests!");
    return 1;
}



