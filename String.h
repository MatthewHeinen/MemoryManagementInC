//
// Created by davew on 10/4/22.
//

#ifndef BIGINT_STRING_H
#define BIGINT_STRING_H

#include <iostream>

// Works for strings of size up to MaxString, fails if we go over
class String {
public:
    explicit String(const char *init);
    String(const String &init);   // control "copy initialization", e.g., "String t = s;" for some String s
    String();                     // control initialization of strings without a given initial value, e.g., "String s;"
    ~String();                    // control destruction of strings, e.g., at "}" for function containing s and t

    int length() const;           // how long is it?

    String &operator=(const String &rhs);  // control assignment, e.g., "t = s;" for existing Strings t and s

    friend String operator+(const String &lhs, const String &rhs);  // allow t+s
    const char &operator[](int index) const;                  // read-only access for, e.g., s[3]
    char &operator[](int index);                              // read/write access for, e.g., s[3]

    friend std::ostream &operator<<(std::ostream &, const String &printMe);             // output operation
// std::istream &operator>>(std::istream &,       String &inputMe);             // input operation ... _changes_ the SafeInt object

private:
    const static int maxSize = 1000;
    char letters[maxSize+1];  // we use C-style null-termination, so provide one more space
    [[nodiscard]] bool repInv() const;      // check the representation invariant, should never return false, typically we assert it
};


void String_Demo();

#endif //BIGINT_STRING_H
