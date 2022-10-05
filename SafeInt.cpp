//
// Created by davew on 9/29/22.
//

#include "SafeInt.h"
#include <exception>  // get domain_error, which we throw if we overflow


// The boring, repetitive part of setting up _member_ and _friend_ functions was done by
//   right-clicking in this file in C-Lion, and choosing "Generate -> Generate Definitions"
//   and then choosing either the class name (for members) or "top-level functions" (for friends, etc.)
//   and then selecting all the ones we want

SafeInt::SafeInt(int i) {
    this->theValue = i;    // We _strongly_ recommend you put "this->" for all initializations in constructor
    // same as   (*this).theValue = i;
    // but _not_  *this .theValue = i;
    // and _not_   this .theValue = i;
    // ToDo: Understand why the above two are wrong
}

SafeInt::SafeInt()
{
    // this->theValue = -666;
}


// This isn't a method, so no "this" pointer is available.
// But, it is listed in the class (as "friend", so it does have access to private fields)
// Defining non-mutating operators as friends allows implicit type-casting of both operands
SafeInt operator+(const SafeInt &lhs, const SafeInt &rhs) {
    // ToDo: figure out how to check for overflow better than this, then throw an exception if we get it
    if (lhs.theValue+rhs.theValue > 2000 or lhs.theValue+rhs.theValue < -2000) {
        throw "domain_error"; // Dave gives up after not being able to #include the domain_error exception  // ToDo:
    }
    return SafeInt(lhs.theValue + rhs.theValue);
}

// Operator+= is in the class without "friend", so it's a method
// It gets access and has a "this" object (the left-hand side, in a += b)
// Defining mutator operators as methods prevents implicit type-casting of the left-hand side
// Note that, in C and C++, assignment operations are "right-associative" and produce a reference to their lhs, so
//      a = b = c = d+e;
//   is the same as
//      a = (b = (c = d+e));
//   is the same as
//      c = d+e;
//      b = c;
//      a = b;
SafeInt &SafeInt::operator+=(const SafeInt &rhs) {
    // The not-too-weird-looking version of the quick-and-easy way to do +=
    SafeInt sum= (*this) + rhs;  // use operator + above
    (*this) = sum;
    return *this;
    // The concise-and-clever version for confident C/C++ programmers
    // return (*this) = (*this) + rhs);  // use the "assignment produces a reference to lhs" property
}


// Since this is supposed to work like a /= operation, we'll make it a method, like +=
SafeInt &SafeInt::divSet(const SafeInt &rhs) {
    return (*this) = (div(*this, rhs));  // use the "assignment produces a reference to lhs" property
}

SafeInt div(const SafeInt &lhs, const SafeInt &rhs) {
    int quotient = lhs.theValue / rhs.theValue;
    return SafeInt(quotient);
    // or, just the one-line version below
    // return SafeInt( lhs.theValue / rhs.theValue );
}

double operator/(const SafeInt &lhs, const SafeInt &rhs) {
    return double(lhs.theValue)/double(rhs.theValue);
}


// A method to type-cast a SafeInt into type "int" ...
SafeInt::operator int() const {
    // could throw bad_cast exception, except that can't happen since SafeInt must be in bounds :-)
    return this->theValue;
}


// Streams return a reference to the stream they used, but are left-associative, so
//      cout << x << y << endl;
//   is the same thing as
//      ((cout << x) << y) << endl;
//   is the same thing as
//      (cout << x);
//      (cout << y);
//      cout << endl;
std::ostream &operator<<(std::ostream &any_ostream, const SafeInt &printMe)             // output operation
{
    return any_ostream << int(printMe);  // ToDo: Think: Why is "cout" wrong here?  Why is "endl" inappropriate?
}
std::istream &operator>>(std::istream &any_istream,       SafeInt &inputMe)             // input operation ... _changes_ the SafeInt object
{
    int readAnInt;  // we could also read characters and convert them...
    any_istream >> readAnInt;
    inputMe = SafeInt(readAnInt);
    return any_istream;
}

using std::cin, std::cout, std::endl, std::cerr;


void SafeInt_Demo()
{
    cout << "Enter a positive integer, and I'll triple it until it makes me sad to do so..." << endl;
    SafeInt n;
    while (cin >> n) {  // Stops when cin fails, due to end-of-input or non-integer entered
        cout << "I read in the value " << n << ", time to start tripling!!!" << endl;
        try {
            while (true) { // run until error
                int one = 1;  // a regular int, to demonstrate casting below
                n = n+n+n;
                n = n + one;   // 1 gets implicitly cast to SafeInt to provide a const SafeInt& parameter to operator+
                n = one + n;   // works for left or right-hand side
                n += one;      // works for right-hand side of operator+=
            //  one += n;      // does not work for left-hand side of operator+=, because that's a non-const member
                n += -3;       // go back down so we're just tripling
                cout << "Managed to triple it and get " << n << endl;
            }
//        } catch (domain_error) {   // AS noted above, Dave gave up on doing this the "right way"
//            cout << "Aha! I thought so ... eventually we got domain_error" << endl;
        } catch (const char *complaint) {
            cout << "Aha! I thought so ... eventually we got domain_error, I think..." << complaint << endl;
        } catch (...) {
            cerr << "Wait, what?  Got some exception other than domain_error, when trying to triple " << n << endl;
        }
    }
}