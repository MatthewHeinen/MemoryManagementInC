//
// Created by davew on 9/29/22.
//  A "SafeInt" is just an int, but ...
//     * it throws ValueError if on overflow, e.g., you add n+n+n, where n is 2/5 of MAXINT
//     * when you divide them, you get a float, like in python; use "div" for integer division those
//     * for now, integer division and mod can produce negative remainders (like in C), we could fix this...
//
//

#ifndef BIGINT_SAFEINT_H
#define BIGINT_SAFEINT_H

#include <iostream>

class SafeInt {
public:         // Unlike Java, we don't have to say "public" and "private" on each member

    explicit SafeInt(const int &i);     // allows implicit typecasting f int to SafeInt, use "explicit" to prevent that
    // by default, SafeInt's can be created uninitialized
    // by default, SafeInt's can be initialized with other SafeInt's
    // by default, SafeInt's can be assigned new SafeInt values
    // see example String class from lecture, for examples of controlling those things

    // Note we can define methods/functions with names that are operator symbols.
    // Mutators like "+=" are done with _methods_; others are done as "friend functions":
    friend SafeInt operator+(const SafeInt &lhs, const SafeInt &rhs);   // called as lhs + rhs
    SafeInt &operator+=(const SafeInt &rhs);                            // called as lhs += rhs; "this" becomes &lhs

    friend SafeInt div(const SafeInt &lhs, const SafeInt &rhs);         // called as lhs / rhs
    SafeInt &divSet(const SafeInt &rhs);                                // called as lhs.divSet(rhs), like lhs/=rhs
    friend double operator/(const SafeInt &lhs, const SafeInt &rhs);     // called as div(lhs, rhs)

    // the type-cast operator below is called via int(value) or (int) value
    //   where "value" is a SafeInt and "this" becomes &value
    // the word "explicit" prevents (usually accidental and problematic) implicit casting from SafeInt to int
    explicit operator int() const;

private:        // Stuff below this line is private, i.e., only for methods ("member functions") and friend functions
    int theValue;
};

// These are useful but don't need to access the private fields, so don't have to be in the class
std::ostream &operator<<(std::ostream &, const SafeInt &printMe);             // output operation
std::istream &operator>>(std::istream &,       SafeInt &inputMe);             // input operation ... _changes_ the SafeInt object

void SafeInt_Demo();

// Bodies of those methods/functions go in SafeInt.cpp, which must be listed in CMakeLists.txt to be compiled;
//   SafeInt.cpp and all files that use SafeInt can #include this .h file, but _not_ the .cpp (as usual).

#endif //BIGINT_SAFEINT_H
